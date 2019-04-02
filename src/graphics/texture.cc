#include "texture.hh"
#include "png.hh"

#include <cstdint>
#include <string>

Texture::Texture(SP<Image> image) //TODO handle 16 bit images in GL
{
	std::vector<uint8_t> imageData;
	for(auto const &pix : image->imageData)
	{
		IR::vec4<uint8_t> pixel = pix.asRGBAui8();
		imageData.push_back(pixel.r());
		imageData.push_back(pixel.g());
		imageData.push_back(pixel.b());
		if(image->colorFormat == PNG::COLOR_FMT_RGBA) imageData.push_back(pixel.a());
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &this->handle);
	glTextureStorage2D(this->handle, 1, image->srgb ? (image->colorFormat == PNG::COLOR_FMT_RGB ? GL_SRGB8 : GL_SRGB8_ALPHA8) : (image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB8 : GL_RGBA8), image->width, image->height);
	glTextureSubImage2D(this->handle, 0, 0, 0, image->width, image->height, image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
	//glTextureSubImage2D(this->handle, 0, 0, 0, image->width, image->height, image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_SHORT, imageData.data()); //TODO enable for 16 bit
	glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	this->filePath = image->filePath;
	this->width = image->width;
	this->height = image->height;
	this->colorFormat = image->colorFormat;
	this->bitDepth = image->bitDepth;
	this->srgb = image->srgb;
}

Texture::Texture(Image &image) //TODO handle 16 bit images in GL
{
	std::vector<uint8_t> imageData;
	for(auto const &pix : image.imageData)
	{
		IR::vec4<uint8_t> pixel = pix.asRGBAui8();
		imageData.push_back(pixel.r());
		imageData.push_back(pixel.g());
		imageData.push_back(pixel.b());
		if(image.colorFormat == PNG::COLOR_FMT_RGBA) imageData.push_back(pixel.a());
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &this->handle);
	glTextureStorage2D(this->handle, 1, image.srgb ? (image.colorFormat == PNG::COLOR_FMT_RGB ? GL_SRGB8 : GL_SRGB8_ALPHA8) : (image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB8 : GL_RGBA8), image.width, image.height);
	glTextureSubImage2D(this->handle, 0, 0, 0, image.width, image.height, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
	//glTextureSubImage2D(this->handle, 0, 0, 0, image.width, image.height, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_SHORT, imageData.data()); //TODO enable for 16 bit
	glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	this->filePath = image.filePath;
	this->width = image.width;
	this->height = image.height;
	this->colorFormat = image.colorFormat;
	this->bitDepth = image.bitDepth;
	this->srgb = image.srgb;
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->handle);
}

void Texture::use(uint32_t target)
{
	glBindTextureUnit(target, this->handle);
}
