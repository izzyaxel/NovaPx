#pragma once

#include "color.hh"

#include <string>

struct Image
{
	Image() = default;
	
	explicit Image(std::string const &filePath, bool srgb = true);
	
	/// Get the pixel at the given x, y position in the image, starting from the top-left, left to right, top to bottom
	Color getPixel(uint32_t x, uint32_t y);
	
	void setPixel(uint32_t x, uint32_t y, Color &color);
	
	/// Get the index into the imageData array based on the x, y position of the pixel given
	size_t index(uint32_t x, uint32_t y);
	
	bool isDirty();
	
	bool hasUnsavedChanges();
	
	/// Is image data present in this image
	bool empty();
	
	uint32_t width = 0, height = 0;
	bool srgb = true;
	char colorFormat = 'a', bitDepth = 'a';
	std::string filePath;
	std::vector<Color> imageData;

private:
	bool dirty = false, diskDirty = true;
};
