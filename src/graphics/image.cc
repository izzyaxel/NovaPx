#include "image.hh"
#include "png.hh"
#include "../util/util.hh"
#include "../util/io.hh"
#include "../util/gui.hh"
#include "../util/globals.hh"

#include <queue>

Image::Image(std::string const &filePath)
{
	PNG png = readPNG(filePath);
	if(png.imageData == nullptr || png.width + png.height == 0 || png.colorFormat == 0 || png.bitDepth == 0) printf("Image Loader: %s could not be read\n", filePath.data());
	this->width = png.width;
	this->height = png.height;
	this->colorFormat = PNG::COLOR_FMT_RGBA;
	this->bitDepth = png.bitDepth;
	this->filePath = filePath;
	uint32_t channels = (png.colorFormat == PNG::COLOR_FMT_RGB ? 3 : 4), stride = channels * (png.bitDepth == 8 ? 1 : 2);
	for(uint32_t i = 0; i < png.height; i++)
	{
		for(uint32_t j = 0; j < png.width; j++)
		{
			Color c;
			if(png.bitDepth == 8)
			{
				uint8_t r, g, b, a;
				r = (png.imageData[i] + j * stride)[0];
				g = (png.imageData[i] + j * stride)[1];
				b = (png.imageData[i] + j * stride)[2];
				if(channels == 4) a = (png.imageData[i] + j * stride)[3];
				else a = ui8Max;
				c.fromRGBAui8(r, g, b, a);
			}
			else if(png.bitDepth == 16)
			{
				uint16_t r, g, b, a;
				r = reinterpret_cast<uint16_t *>(png.imageData[i] + j * stride)[0];
				g = reinterpret_cast<uint16_t *>(png.imageData[i] + j * stride)[1];
				b = reinterpret_cast<uint16_t *>(png.imageData[i] + j * stride)[2];
				if(channels == 4) a = reinterpret_cast<uint16_t *>(png.imageData[i] + j * stride)[3];
				else a = ui16Max;
				c.fromRGBAui16(r, g, b, a);
			}
			this->imageData.push_back(c);
		}
	}
	this->setNeedsRedraw();
}

size_t Image::index(int32_t x, int32_t y)
{
	return x + (y * this->width);
}

bool Image::areCoordsValid(int32_t x, int32_t y)
{
	return x >= 0 && y >= 0 && static_cast<uint32_t>(x) < this->width && static_cast<uint32_t>(y) < this->height;
}

void Image::floodFill(int32_t x, int32_t y, Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	std::queue<IR::vec2<int32_t>> pixels;
	pixels.emplace(x, y);
	do
	{
		IR::vec2<int32_t> p = pixels.front();
		int32_t pX = p.x(), pY = p.y();
		pixels.pop();
		this->setPixel(p.x(), p.y(), newColor);
		if(this->areCoordsValid(pX + 1, pY) && this->getPixel(pX + 1, pY) == oldColor) pixels.emplace(pX + 1, pY);
		if(this->areCoordsValid(pX - 1, pY) && this->getPixel(pX - 1, pY) == oldColor) pixels.emplace(pX - 1, pY);
		if(this->areCoordsValid(pX, pY + 1) && this->getPixel(pX, pY + 1) == oldColor) pixels.emplace(pX, pY + 1);
		if(this->areCoordsValid(pX, pY - 1) && this->getPixel(pX, pY - 1) == oldColor) pixels.emplace(pX, pY - 1);
	} while(!pixels.empty());
}

void Image::floodFillDiagonal(int32_t x, int32_t y, Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	std::queue<IR::vec2<int32_t>> pixels;
	pixels.emplace(x, y);
	do
	{
		IR::vec2<int32_t> p = pixels.front();
		int32_t pX = p.x(), pY = p.y();
		pixels.pop();
		this->setPixel(p.x(), p.y(), newColor);
		if(this->areCoordsValid(pX + 1, pY) && this->getPixel(pX + 1, pY) == oldColor) pixels.emplace(pX + 1, pY);
		if(this->areCoordsValid(pX - 1, pY) && this->getPixel(pX - 1, pY) == oldColor) pixels.emplace(pX - 1, pY);
		if(this->areCoordsValid(pX, pY + 1) && this->getPixel(pX, pY + 1) == oldColor) pixels.emplace(pX, pY + 1);
		if(this->areCoordsValid(pX, pY - 1) && this->getPixel(pX, pY - 1) == oldColor) pixels.emplace(pX, pY - 1);
		if(this->areCoordsValid(pX + 1, pY + 1) && this->getPixel(pX + 1, pY + 1) == oldColor) pixels.emplace(pX + 1, pY + 1);
		if(this->areCoordsValid(pX - 1, pY - 1) && this->getPixel(pX - 1, pY - 1) == oldColor) pixels.emplace(pX - 1, pY - 1);
		if(this->areCoordsValid(pX - 1, pY + 1) && this->getPixel(pX - 1, pY + 1) == oldColor) pixels.emplace(pX - 1, pY + 1);
		if(this->areCoordsValid(pX + 1, pY - 1) && this->getPixel(pX + 1, pY - 1) == oldColor) pixels.emplace(pX + 1, pY - 1);
	} while(!pixels.empty());
}

void Image::replaceColor(Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	for(auto &pixel : this->imageData) if(pixel == oldColor) pixel = newColor;
}

Color Image::getPixel(int32_t x, int32_t y)
{
	return this->imageData[this->index(x, y)];
}

void Image::setPixel(int32_t x, int32_t y, Color &color)
{
	this->imageData[this->index(x, y)] = color;
	this->setNeedsRedraw();
	this->setHasUnsavedChanges();
}

bool Image::needsRedraw()
{
	return this->_needsRedraw;
}

void Image::setNeedsRedraw()
{
	this->_needsRedraw = true;
}

bool Image::hasUnsavedChanges()
{
	return this->_unsavedChanges;
}

void Image::setHasUnsavedChanges()
{
	this->_unsavedChanges = true;
}

bool Image::empty()
{
	return this->imageData.empty();
}

void Image::setMagLabel()
{
	magLabel->setText(QString::fromStdString("Zoom: " + std::to_string(this->scale.x()) + "x"));
}

void Image::limitScale()
{
	if(this->scale.x() < Camera::minZoom) this->scale.x() = Camera::minZoom;
	if(this->scale.y() < Camera::minZoom) this->scale.y() = Camera::minZoom;
	if(this->scale.x() > Camera::maxZoom) this->scale.x() = Camera::maxZoom;
	if(this->scale.y() > Camera::maxZoom) this->scale.y() = Camera::maxZoom;
}

void Image::setScale(IR::vec2<float> const &scale)
{
	this->scale = scale;
	this->limitScale();
	this->setNeedsRedraw();
	this->setMagLabel();
}

void Image::addScale(IR::vec2<float> const &scale)
{
	this->scale += scale;
	this->limitScale();
	this->setNeedsRedraw();
	this->setMagLabel();
}
