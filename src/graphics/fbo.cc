#include "fbo.hh"

#include <glad/glad.h>
#include <vector>
#include <cstdio>

UP<FBOPool> fboPool = nullptr;

void initFBOPool(size_t alloc, uint32_t width, uint32_t height)
{
	fboPool = MU<FBOPool>(alloc, width, height);
}

void createFBO(FBO &fbo)
{
	glCreateFramebuffers(1, &fbo.handle);
	fbo.bindFBO();
	glViewport(0, 0, fbo.width, fbo.height);
	glScissor(0, 0, fbo.width, fbo.height);
	if(fbo.hasColor) glCreateTextures(GL_TEXTURE_2D, 1, &fbo.colorHandle);
	if(fbo.hasDepth) glCreateTextures(GL_TEXTURE_2D, 1, &fbo.depthHandle);
	glTextureStorage2D(fbo.colorHandle, 1, fbo.hasAlpha ? GL_RGBA32F : GL_RGB32F, fbo.width, fbo.height);
	glNamedFramebufferTexture(fbo.handle, GL_COLOR_ATTACHMENT0, fbo.colorHandle, 0);
	if(fbo.hasDepth)
	{
		glTextureStorage2D(fbo.depthHandle, 1, GL_DEPTH_COMPONENT32F, fbo.width, fbo.height);
		glNamedFramebufferTexture(fbo.handle, GL_DEPTH_ATTACHMENT, fbo.depthHandle, 0);
	}
	std::vector<GLenum> drawBuffers;
	drawBuffers.emplace_back(GL_COLOR_ATTACHMENT0);
	if(fbo.hasDepth) drawBuffers.emplace_back(GL_COLOR_ATTACHMENT1);
	glNamedFramebufferDrawBuffers(fbo.handle, static_cast<int32_t>(drawBuffers.size()), drawBuffers.data());
	GLenum error = glCheckNamedFramebufferStatus(fbo.handle, GL_FRAMEBUFFER);
	if(error != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FBO Creation Error: ");
		switch(error)
		{
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: printf("incomplete attachment\n"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT: printf("incomplete dimensions\n"); break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: printf("missing attachment\n"); break;
			case GL_FRAMEBUFFER_UNSUPPORTED: printf("FBOs are not supported\n"); break;
			default: break;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void clearFBO(FBO &fbo)
{
	glDeleteFramebuffers(1, &fbo.handle);
	glDeleteTextures(1, &fbo.colorHandle);
	glDeleteTextures(1, &fbo.depthHandle);
}

FBO::FBO(uint32_t width, uint32_t height, AttachmentType options, std::string const &name)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->hasColor = options & this->COLOR;
	this->hasAlpha = options & this->ALPHA;
	this->hasDepth = options & this->DEPTH;
	this->hasStencil = options & this->STENCIL;
	createFBO(*this);
}

FBO::~FBO()
{
	clearFBO(*this);
}

void FBO::bindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->handle);
}

void FBO::bindColor(uint32_t target)
{
	glBindTextureUnit(target, this->colorHandle);
}

void FBO::bindDepth(uint32_t target)
{
	glBindTextureUnit(target, this->depthHandle);
}

void FBO::regen(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
	clearFBO(*this);
	createFBO(*this);
}

void FBO::print()
{
	if(this->hasColor) printf("Color Handle: %u\n", this->colorHandle);
	if(this->hasDepth) printf("Depth Handle: %u\n", this->depthHandle);
	printf("Has Alpha: %s\n", this->hasAlpha ? "true" : "false");
	printf("Name: %s\n", this->name.data());
	printf("W: %u H: %u\n\n", this->width, this->height);
}

FBOPool::FBOPool(size_t alloc, uint32_t width, uint32_t height)
{
	this->pool.resize(alloc);
	for(size_t i = 0; i < alloc; i++)
	{
		this->pool[i] = MS<FBO>(width, height, FBO::COLOR | FBO::ALPHA | FBO::DEPTH, "Pool " + std::to_string(i));
	}
}

SP<FBO> FBOPool::getNextAvailableFBO(uint32_t width, uint32_t height)
{
	SP<FBO> out;
	for(auto &fbo : this->pool)
	{
		if(fbo.use_count() == 1)
		{
			if(fbo->width != width || fbo->height != height)
			{
				fbo = MS<FBO>(width, height, FBO::COLOR | FBO::ALPHA | FBO::DEPTH, "Pool " + std::to_string(this->pool.size() + 1));
			}
			fbo->bindFBO();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			return fbo;
		}
	}
	this->pool.push_back(MS<FBO>(width, height, FBO::COLOR | FBO::ALPHA | FBO::DEPTH, "Pool " + std::to_string(this->pool.size() + 1)));
	this->pool.back()->bindFBO();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return this->pool.back();
}
