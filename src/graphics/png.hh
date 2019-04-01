#pragma once

#include <string>
#include <cstdint>

struct PNG
{
	static int32_t constexpr COLOR_FMT_GREY = 0;
	static int32_t constexpr COLOR_FMT_PALETTE = 2 | 1;
	static int32_t constexpr COLOR_FMT_RGB = 2;
	static int32_t constexpr COLOR_FMT_RGBA = 2 | 4;
	static int32_t constexpr COLOR_FMT_GREY_ALPHA = 4;
	
	PNG(uint32_t width, uint32_t height, char colorFormat, char bitDepth, unsigned char** &&imageData);
	
	~PNG();
	
	///The width and height of the image in pixels
	uint32_t width, height;
	
	///The color format and depth width the decoded data is in
	char colorFormat, bitDepth;
	
	/// The decoded pixel data
	unsigned char **imageData;
};
