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
	this->imageData.resize(this->height);
	for(uint32_t y = 0; y < this->height; y++)
	{
		this->imageData[y].resize(this->width);
		for(uint32_t x = 0; x < this->width; x++)
		{
			Color c;
			if(png.bitDepth == 8)
			{
				uint8_t r, g, b, a;
				r = (png.imageData[y] + x * stride)[0];
				g = (png.imageData[y] + x * stride)[1];
				b = (png.imageData[y] + x * stride)[2];
				if(channels == 4) a = (png.imageData[y] + x * stride)[3];
				else a = ui8Max;
				c.fromRGBAui8(r, g, b, a);
			}
			else if(png.bitDepth == 16)
			{
				uint16_t r, g, b, a;
				r = reinterpret_cast<uint16_t *>(png.imageData[y] + x * stride)[0];
				g = reinterpret_cast<uint16_t *>(png.imageData[y] + x * stride)[1];
				b = reinterpret_cast<uint16_t *>(png.imageData[y] + x * stride)[2];
				if(channels == 4) a = reinterpret_cast<uint16_t *>(png.imageData[y] + x * stride)[3];
				else a = ui16Max;
				c.fromRGBAui16(r, g, b, a);
			}
			this->imageData[y].push_back(c);
		}
	}
	for(uint32_t i = 0; i < this->height; i++) this->scanlineDirty[i] = true;
	this->setNeedsRedraw();
}

void Image::updateQImageRGBA64(QImage &qImage)
{
	for(uint32_t i = 0; i < this->height; i++)
	{
		if(this->scanlineDirty[i]) memcpy(qImage.scanLine(i), this->scanlineRGBA64(i), this->width * (sizeof(uint16_t) * 4));
		this->scanlineDirty[i] = false;
	}
}

void Image::updateQImageARGB32(QImage &qImage)
{
	/*for(uint32_t i = 0; i < this->height; i++)
	{
		if(this->scanlineDirty[i]) memcpy(qImage.scanLine(i), this->scanlineARGB32(i), this->width * (sizeof(uint8_t) * 4));
		this->scanlineDirty[i] = false;
	}*/
	for(uint32_t y = 0; y < this->height; y++)
	{
		QRgb * scanline = reinterpret_cast<QRgb *>(qImage.scanLine(y));
		for(uint32_t x = 0; x < this->width; x++)
		{
			auto color = this->getPixel(x, y);
			scanline[x] = qRgba(color.data.r(), color.data.g(), color.data.b(), color.data.a());
		}
	}
}

uint16_t* Image::scanlineRGBA64(int row)
{
	return reinterpret_cast<uint16_t *>(this->imageData[row].data());
}

uint8_t* Image::scanlineARGB32(int row)
{
	std::vector<uint8_t> data;
	for(auto const &c : this->imageData[row])
	{
		auto color = c.asRGBAui8();
		data.push_back(color.a());
		data.push_back(color.r());
		data.push_back(color.g());
		data.push_back(color.b());
	}
	return data.data();
}

bool Image::areCoordsValid(int32_t x, int32_t y)
{
	return x >= 0 && y >= 0 && static_cast<uint32_t>(x) < this->width && static_cast<uint32_t>(y) < this->height;
}

void Image::floodFill(int32_t x, int32_t y, Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	std::queue<vec2<int32_t>> pixels;
	pixels.emplace(x, y);
	do
	{
		vec2<int32_t> p = pixels.front();
		int32_t pX = p.x(), pY = p.y();
		pixels.pop();
		this->setPixel(pX, pY, newColor);
		this->scanlineDirty[pY] = true;
		if(this->areCoordsValid(pX + 1, pY) && this->getPixel(pX + 1, pY) == oldColor) pixels.emplace(pX + 1, pY);
		if(this->areCoordsValid(pX - 1, pY) && this->getPixel(pX - 1, pY) == oldColor) pixels.emplace(pX - 1, pY);
		if(this->areCoordsValid(pX, pY + 1) && this->getPixel(pX, pY + 1) == oldColor)
		{
			pixels.emplace(pX, pY + 1);
			this->scanlineDirty[pY + 1] = true;
		}
		if(this->areCoordsValid(pX, pY - 1) && this->getPixel(pX, pY - 1) == oldColor)
		{
			pixels.emplace(pX, pY - 1);
			this->scanlineDirty[pY - 1] = true;
		}
	} while(!pixels.empty());
	this->setNeedsRedraw();
	this->setHasUnsavedChanges();
}

void Image::floodFillDiagonal(int32_t x, int32_t y, Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	std::queue<vec2<int32_t>> pixels;
	pixels.emplace(x, y);
	do
	{
		vec2<int32_t> p = pixels.front();
		int32_t pX = p.x(), pY = p.y();
		pixels.pop();
		this->setPixel(pX, pY, newColor);
		this->scanlineDirty[pY] = true;
		if(this->areCoordsValid(pX + 1, pY) && this->getPixel(pX + 1, pY) == oldColor) pixels.emplace(pX + 1, pY);
		if(this->areCoordsValid(pX - 1, pY) && this->getPixel(pX - 1, pY) == oldColor) pixels.emplace(pX - 1, pY);
		if(this->areCoordsValid(pX, pY + 1) && this->getPixel(pX, pY + 1) == oldColor)
		{
			pixels.emplace(pX, pY + 1);
			this->scanlineDirty[pY + 1] = true;
		}
		if(this->areCoordsValid(pX, pY - 1) && this->getPixel(pX, pY - 1) == oldColor)
		{
			pixels.emplace(pX, pY - 1);
			this->scanlineDirty[pY - 1] = true;
		}
		if(this->areCoordsValid(pX + 1, pY + 1) && this->getPixel(pX + 1, pY + 1) == oldColor)
		{
			pixels.emplace(pX + 1, pY + 1);
			this->scanlineDirty[pY + 1] = true;
		}
		if(this->areCoordsValid(pX - 1, pY - 1) && this->getPixel(pX - 1, pY - 1) == oldColor)
		{
			pixels.emplace(pX - 1, pY - 1);
			this->scanlineDirty[pY - 1] = true;
		}
		if(this->areCoordsValid(pX - 1, pY + 1) && this->getPixel(pX - 1, pY + 1) == oldColor)
		{
			pixels.emplace(pX - 1, pY + 1);
			this->scanlineDirty[pY + 1] = true;
		}
		if(this->areCoordsValid(pX + 1, pY - 1) && this->getPixel(pX + 1, pY - 1) == oldColor)
		{
			pixels.emplace(pX + 1, pY - 1);
			this->scanlineDirty[pY - 1] = true;
		}
	} while(!pixels.empty());
	this->setNeedsRedraw();
	this->setHasUnsavedChanges();
}

void Image::replaceColor(Color &oldColor, Color &newColor)
{
	if(oldColor == newColor) return;
	for(uint32_t y = 0; y < this->height; y++)
	{
		for(uint32_t x = 0; x < this->width; x++)
		{
			if(this->imageData[y][x] == oldColor)
			{
				this->imageData[y][x] = newColor;
				this->scanlineDirty[y] = true;
			}
		}
	}
}

Color Image::getPixel(int32_t x, int32_t y)
{
	return this->imageData[y][x];
	//return this->imageData[this->index(x, y)];
}

void Image::setPixel(int32_t x, int32_t y, Color &color)
{
	//this->imageData[this->index(x, y)] = color;
	this->imageData[y][x] = color;
	this->scanlineDirty[y] = true;
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
	magLabel->setText(QString::fromStdString("Zoom: " + std::to_string(static_cast<int32_t>(this->scale.x())) + "x"));
}

void Image::limitScale()
{
	if(this->scale.x() < (float)Camera::minZoom) this->scale.x() = (float)Camera::minZoom;
	if(this->scale.y() < (float)Camera::minZoom) this->scale.y() = (float)Camera::minZoom;
	if(this->scale.x() > (float)Camera::maxZoom) this->scale.x() = (float)Camera::maxZoom;
	if(this->scale.y() > (float)Camera::maxZoom) this->scale.y() = (float)Camera::maxZoom;
}

void Image::setScale(vec2<float> const &scale)
{
	this->scale = scale;
	this->limitScale();
	this->setNeedsRedraw();
	this->setMagLabel();
}

void Image::addScale(vec2<float> const &scale)
{
	this->scale += scale;
	this->limitScale();
	this->setNeedsRedraw();
	this->setMagLabel();
}
