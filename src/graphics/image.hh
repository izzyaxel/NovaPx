#pragma once

#include "color.hh"

#include <string>
#include <iris/vec2.hh>

struct Image
{
	Image() = default;
	
	explicit Image(std::string const &filePath);
	
	/// Get the pixel at the given x, y position in the image, starting from the top-left, left to right, top to bottom
	Color getPixel(uint32_t x, uint32_t y);
	
	void setPixel(uint32_t x, uint32_t y, Color &color);
	
	/// Get the index into the imageData array based on the x, y position of the pixel given
	size_t index(uint32_t x, uint32_t y);
	
	bool needsRedraw();
	
	void setNeedsRedraw();
	
	bool hasUnsavedChanges();
	
	void setHasUnsavedChanges();
	
	void setScale(IR::vec2<int32_t> const &scale);
	
	void addScale(IR::vec2<int32_t> const &scale);
	
	/// Is image data present in this image
	bool empty();
	
	uint32_t width = 0, height = 0;
	char colorFormat = 'a', bitDepth = 'a';
	std::string filePath;
	std::vector<Color> imageData;
	IR::vec2<int32_t> scale{1, 1};

private:
	bool _needsRedraw = false, _unsavedChanges = true;
};
