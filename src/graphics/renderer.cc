#include "renderer.hh"
#include "../util/util.hh"
#include "shader.hh"
#include "mesh.hh"
#include "../assets/shaders.hh"
#include "../assets/meshes.hh"
#include "texture.hh"
#include "../util/globals.hh"
#include "../util/threadPool.hh"

#include <algorithm>
#include <iris/quaternion.hh>
#include <ctime>

UP<Shader> objectShader;
UP<Mesh> llQuadMesh, orthoQuadMesh;

/// Access types for compute shader imnage binding
enum struct IO
{
	READ = 0x88B8, WRITE = 0x88B9, READWRITE = 0x88BA
};

/// Color format for compute shader image binding
enum struct CF
{
	R32F = 0x822E, RGB8 = 0x8051, RGBA8 = 0x8058, RGB16 = 0x8054, RGBA16 = 0x805B, RGB32I = 0x8D83, RGBA32I = 0x8D82,
	RGB32UI = 0x8D71, RGBA32UI = 0x8D70, RGB16F = 0x881B, RGBA16F = 0x881A, RGB32F = 0x8815, RGBA32F = 0x8814,
	DEPTH32F = 0x8CAC,
};

/// Mode to draw a VAO in
enum struct DrawMode
{
	TRIS = 0x0004, TRISTRIPS = 0x0005, TRIFANS = 0x0006,
	LINES = 0x0001, LINESTRIPS = 0x0003, LINELOOPS = 0x0002,
	POINTS = 0x0000,
};

void draw(DrawMode mode, int32_t numElements, QOpenGLFunctions_4_5_Core *funcs)
{
	funcs->glDrawArrays(static_cast<GLenum>(mode), 0, numElements);
}

void bindImage(uint32_t target, uint32_t const &handle, IO mode, CF format, QOpenGLFunctions_4_5_Core *funcs)
{
	funcs->glBindImageTexture(target, handle, 0, GL_FALSE, 0, static_cast<uint32_t>(mode), static_cast<uint32_t>(format));
}

uint32_t workSizeX = 40, workSizeY = 20;
void startComputeShader(uint32_t contextWidth, uint32_t contextHeight, QOpenGLFunctions_4_5_Core *funcs)
{
	funcs->glDispatchCompute(static_cast<uint32_t>(std::ceil(static_cast<float>(contextWidth) / workSizeX)), static_cast<uint32_t>(std::ceil(static_cast<float>(contextHeight) / workSizeY)), 1);
}

void initAssets()
{
	objectShader = MU<Shader>(defaultVertSource, defaultFragSource);
	llQuadMesh = MU<Mesh>(llQuadVerts, 12, llQuadUVs, 8);
	orthoQuadMesh = MU<Mesh>(orthoQuadVerts, 12, orthoQuadUVs, 8);
}

void destroyAssets()
{
	objectShader.reset();
	llQuadMesh.reset();
	orthoQuadMesh.reset();
}

Renderer::Renderer(QOpenGLFunctions_4_5_Core *funcs)
{
	initAssets();
	funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	funcs->glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

Renderer::~Renderer()
{
	destroyAssets();
}

void Renderer::render(QOpenGLFunctions_4_5_Core *funcs)
{
	funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->v = IR::mat4x4<float>::viewMatrix(IR::quat<float>{}, IR::vec3<float>{camera->pos, 0});
	this->p = IR::mat4x4<float>::orthoProjectionMatrix(0, Context::width, Context::height, 0, 0, 1);
	
	//Render the canvas
	if(canvas && !canvas->empty() && canvas->isDirty())
	{
		this->m = IR::mat4x4<float>::modelMatrix(IR::vec3<float>(0, 0, -1), IR::quat<float>{}, IR::vec3<float>(canvas->width, canvas->height, 1));
		this->mvp = IR::mat4x4<float>::modelViewProjectionMatrix(this->m, this->v, this->p);
		objectShader->use();
		objectShader->sendMat4f("mvp", this->mvp);
		llQuadMesh->use();
		MS<Texture>(canvas)->use();
		draw(DrawMode::TRISTRIPS, llQuadMesh->numVerts, funcs);
	}
}

void Renderer::onResize(QOpenGLFunctions_4_5_Core *funcs)
{
	funcs->glViewport(0, 0, Context::width, Context::height);
	funcs->glScissor(0, 0, Context::width, Context::height);
}

void screenshotIOThread(std::string const &folderPath, uint32_t width, uint32_t height, std::vector<unsigned char> pixels)
{
	createDirectory(folderPath); //Create the screenshots directory if it doesn't exist
	std::string fileName = "Screenshot ";
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	char dt[16];
	strftime(dt, 16, "%m-%d-%y %H%M%S", &tm); //Produce a formatted date and time string for the filename
	fileName += dt;
	fileName += ".png";
	unsigned char **pngData = new unsigned char *[height * sizeof(unsigned char *)]; //Reorder the data into rows for libpng
	for(unsigned int i = 0; i < height; i++) pngData[i] = new unsigned char[width * 3];
	for(unsigned int x = 0; x < height; x++) memcpy(pngData[height - x - 1], pixels.data() + x * (width * 3), width * 3);
	writePNG(folderPath + fileName, width, height, pngData); //Call to Beast to write the PNG file to disk
	for(uint32_t i = 0; i < height; i++) delete[] pngData[i];
	delete[] pngData;
}

void Renderer::screenshot(std::string const &folderPath, uint32_t width, uint32_t height, QOpenGLFunctions_4_5_Core *funcs)
{
	std::vector<unsigned char> pixels;
	pixels.resize(width * height * 3); //Preallocate
	funcs->glPixelStorei(GL_PACK_ALIGNMENT, 1); //Ensure the pixel data we get from OGL is in the right format
	funcs->glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()); //Grab the pixels currently in the buffer and store them in the vector
	threadPool.enqueue(screenshotIOThread, folderPath, width, height, pixels); //I/O will cause a hiccup in the framerate if we don't spin it off into a new asynchronous thread 
}
