#include "renderer.hh"
#include "gl.hh"
#include "../util/util.hh"
#include "shader.hh"
#include "mesh.hh"
#include "../assets/shaders.hh"
#include "../assets/meshes.hh"
#include "texture.hh"

#include <glad/glad.h>
#include <algorithm>
#include <SDL2/SDL_video.h>
#include <iris/quaternion.hh>

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

void Renderer::render(Image &canvas, Camera &camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->v = IR::mat4x4<float>::viewMatrix(IR::quat<float>{}, IR::vec3<float>{camera.pos, 0});
	this->p = IR::mat4x4<float>::orthoProjectionMatrix(0, this->contextWidth, this->contextHeight, 0, 0, 1);
	
	//Render the UI
	
	
	//Render the canvas
	if(!canvas.empty() && canvas.isDirty())
	{
		this->m = IR::mat4x4<float>::modelMatrix(IR::vec3<float>(0, 0, -1), IR::quat<float>{}, IR::vec3<float>(canvas.width, canvas.height, 1));
		this->mvp = IR::mat4x4<float>::modelViewProjectionMatrix(this->m, this->v, this->p);
		objectShader->use();
		objectShader->sendMat4f("mvp", this->mvp);
		llQuadMesh->use();
		MS<Texture>(canvas)->use();
		draw(DrawMode::TRISTRIPS, llQuadMesh->numVerts);
	}
}

void Renderer::onResize(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
}
