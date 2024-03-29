#pragma once

#include "color.hh"

#include <string>
#include <commons/math/vec2.hh>
#include <QtGui/QImage>
#include <unordered_map>

struct Image
{
	Image() = default;
	
	explicit Image(std::string const &filePath);
	
	void updateQImageRGBA64(QImage &qImage);
	
	void updateQImageARGB32(QImage &qImage);
	
	uint16_t* scanlineRGBA64(int row);
	
	uint8_t* scanlineARGB32(int row);
	
	/// Get the pixel at the given x, y position in the image, starting from the top-left, left to right, top to bottom
	Color getPixel(int32_t x, int32_t y);
	
	void setPixel(int32_t x, int32_t y, Color &color);
	
	bool needsRedraw();
	
	void setNeedsRedraw();
	
	bool hasUnsavedChanges();
	
	void setHasUnsavedChanges();
	
	void setScale(vec2<float> const &scale);
	
	void addScale(vec2<float> const &scale);
	
	/// Non-recursive (prevents stack overflows) flood fill
	void floodFill(int32_t x, int32_t y, Color &oldColor, Color &newColor);
	
	/// Non-recursive flood fill that affects diagonally touching pixels
	void floodFillDiagonal(int32_t x, int32_t y, Color &oldColor, Color &newColor);
	
	/// Replace all instances of the given color with a new color
	void replaceColor(Color &oldColor, Color &newColor);
	
	/// Is image data present in this image
	bool empty();
	
	void setMagLabel();
	
	uint32_t width = 0, height = 0;
	char colorFormat = 'a', bitDepth = 'a';
	std::string filePath;
	std::vector<std::vector<Color>> imageData;
	vec2<float> scale{1};
	std::unordered_map<uint32_t, bool> scanlineDirty;

private:
	void limitScale();
	bool areCoordsValid(int32_t x, int32_t y);
	
	bool _needsRedraw = false, _unsavedChanges = true;
};
