#include "image.hh"
#include "png.hh"
#include "../util/util.hh"
#include "../util/io.hh"

Image::Image(std::string const &filePath)
{
	PNG png = readPNG(filePath);
	if(png.imageData == nullptr || png.width + png.height == 0 || png.colorFormat == 0 || png.bitDepth == 0) printf("Image Loader: %s could not be read\n", filePath.data());
	this->width = png.width;
	this->height = png.height;
	this->colorFormat = png.colorFormat;
	this->bitDepth = png.bitDepth;
	this->filePath = filePath;
	uint32_t channels = (png.colorFormat == PNG::COLOR_FMT_RGB ? 3 : 4), stride = channels * (png.bitDepth == 8 ? 1 : 2);
	uint8_t** imageData = reinterpret_cast<uint8_t**>(png.imageData);
	for(uint32_t i = 0; i < png.height; i++)
	{
		for(uint32_t j = 0; j < png.width; j++)
		{
			Color c;
			if(png.bitDepth == 8)
			{
				uint8_t r, g, b, a;
				r = (imageData[i] + j * stride)[0];
				g = (imageData[i] + j * stride)[1];
				b = (imageData[i] + j * stride)[2];
				if(channels == 4) a = (imageData[i] + j * stride)[3];
				else a = ui8Max;
				c.fromRGBAui8(r, g, b, a);
			}
			else if(png.bitDepth == 16)
			{
				uint16_t r, g, b, a;
				r = reinterpret_cast<uint16_t *>(imageData[i] + j * stride)[0];
				g = reinterpret_cast<uint16_t *>(imageData[i] + j * stride)[1];
				b = reinterpret_cast<uint16_t *>(imageData[i] + j * stride)[2];
				if(channels == 4) a = reinterpret_cast<uint16_t *>(imageData[i] + j * stride)[3];
				else a = ui16Max;
				c.fromRGBAui16(r, g, b, a);
			}
			this->imageData.push_back(c);
		}
	}
}

size_t Image::index(uint32_t x, uint32_t y)
{
	return x + (y * this->width);
}

Color Image::getPixel(uint32_t x, uint32_t y)
{
	return this->imageData[this->index(x, y)];
}

void Image::setPixel(uint32_t x, uint32_t y, Color &color)
{
	this->imageData[this->index(x, y)] = color;
	this->dirty = true;
}

bool Image::isDirty()
{
	return this->dirty;
}

void Image::markDirty()
{
	this->dirty = true;
}

bool Image::hasUnsavedChanges()
{
	return this->diskDirty;
}

bool Image::empty()
{
	return this->imageData.empty();
}
