#include "renderer.hh"
#include "../util/util.hh"
#include "shader.hh"
#include "mesh.hh"
#include "../assets/shaders.hh"
#include "../assets/meshes.hh"
#include "texture.hh"
#include "../info/globals.hh"
#include "../util/threadPool.hh"

#include <algorithm>
#include <iris/quaternion.hh>
#include <ctime>

UP<Shader> objectShader;
UP<Mesh> llQuadMesh, orthoQuadMesh;

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

Renderer::Renderer()
{
	initAssets();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

Renderer::~Renderer()
{
	destroyAssets();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->v = IR::mat4x4<float>::viewMatrix(IR::quat<float>{}, IR::vec3<float>{camera->pos, 0});
	this->p = IR::mat4x4<float>::orthoProjectionMatrix(0, this->contextWidth, this->contextHeight, 0, 0, 1);
	
	//Render the UI
	
	
	//Render the canvas
	if(!canvas->empty() && canvas->isDirty())
	{
		this->m = IR::mat4x4<float>::modelMatrix(IR::vec3<float>(0, 0, -1), IR::quat<float>{}, IR::vec3<float>(canvas->width, canvas->height, 1));
		this->mvp = IR::mat4x4<float>::modelViewProjectionMatrix(this->m, this->v, this->p);
		objectShader->use();
		objectShader->sendMat4f("mvp", this->mvp);
		llQuadMesh->use();
		MS<Texture>(canvas)->use();
		draw(DrawMode::TRISTRIPS, llQuadMesh->numVerts);
	}
}

void Renderer::onResize()
{
	glViewport(0, 0, Context::width, Context::height);
	glScissor(0, 0, Context::width, Context::height);
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

void Renderer::screenshot(std::string const &folderPath, uint32_t width, uint32_t height)
{
	std::vector<unsigned char> pixels;
	pixels.resize(width * height * 3); //Preallocate
	glPixelStorei(GL_PACK_ALIGNMENT, 1); //Ensure the pixel data we get from OGL is in the right format
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()); //Grab the pixels currently in the buffer and store them in the vector
	threadPool.enqueue(screenshotIOThread, folderPath, width, height, pixels); //I/O will cause a hiccup in the framerate if we don't spin it off into a new asynchronous thread 
}

void Renderer::draw(DrawMode mode, int32_t numElements)
{
	glDrawArrays(static_cast<GLenum>(mode), 0, numElements);
}
