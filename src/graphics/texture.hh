#pragma once

#include "image.hh"
#include "../util/def.hh"

#include <cstdint>
#include <string>

struct Texture
{
	Texture(Image &image);
	
	~Texture();
	
	void use(uint32_t target = 0);
	
	std::string filePath;
	uint32_t handle;
	uint32_t width, height;
	char colorFormat, bitDepth;
	bool srgb;
};
