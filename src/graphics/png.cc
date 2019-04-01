#include "png.hh"

PNG::PNG(uint32_t width, uint32_t height, char colorFormat, char bitDepth, unsigned char** &&imageData) : width(width), height(height), colorFormat(colorFormat), bitDepth(bitDepth), imageData(imageData){}

PNG::~PNG()
{
	for(uint32_t i = 0; i < this->height; i++) delete[] this->imageData[i];
	delete[] this->imageData;
}
