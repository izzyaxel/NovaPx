#pragma once

#include "image.hh"
#include "../util/def.hh"

#include <cstdint>
#include <string>
#include <QtGui/QOpenGLFunctions_4_5_Core>

struct Texture : QOpenGLFunctions_4_5_Core
{
	Texture(std::string const &textureFilePath);
	Texture(SP<Image> image);
	Texture(Image &image);
	
	~Texture();
	
	void use(uint32_t target = 0);
	
	std::string filePath;
	uint32_t handle;
	uint32_t width, height;
	char colorFormat, bitDepth;
};
