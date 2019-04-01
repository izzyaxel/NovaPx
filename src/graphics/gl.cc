#include "gl.hh"

#include <glad/glad.h>
#include <cmath>

void bindImage(uint32_t target, uint32_t const &handle, IO mode, CF format)
{
	glBindImageTexture(target, handle, 0, GL_FALSE, 0, static_cast<uint32_t>(mode), static_cast<uint32_t>(format));
}

uint32_t workSizeX = 40, workSizeY = 20;

void startComputeShader(uint32_t contextWidth, uint32_t contextHeight)
{
	glDispatchCompute(static_cast<uint32_t>(std::ceil(static_cast<float>(contextWidth) / workSizeX)), static_cast<uint32_t>(std::ceil(static_cast<float>(contextHeight) / workSizeY)), 1);
}

void draw(DrawMode mode, int32_t numElements)
{
	glDrawArrays(static_cast<GLenum>(mode), 0, numElements);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
