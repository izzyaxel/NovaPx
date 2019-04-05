#include "texture.hh"
#include "png.hh"
#include "../util/io.hh"

#include <cstdint>
#include <string>

Texture::Texture(std::string const &textureFilePath)
{
	this->initializeOpenGLFunctions();
	PNG image = readPNG(textureFilePath);
	if(image.imageData == nullptr || image.width + image.height == 0 || image.colorFormat == 0 || image.bitDepth == 0)
	{
		printf("Texture Loader: %s could not be read\n", textureFilePath.data());
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &this->handle);
	glTextureStorage2D(this->handle, 1, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB8 : GL_RGBA8, image.width, image.height);
	for(uint32_t i = 0; i < image.height; i++) glTextureSubImage2D(this->handle, 0, 0, i, image.width, 1, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image.imageData[i]);
	this->glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	this->glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	this->filePath = textureFilePath;
	this->width = image.width;
	this->height = image.height;
	this->colorFormat = image.colorFormat;
	this->bitDepth = image.bitDepth;
}

Texture::Texture(SP<Image> image) //TODO handle 16 bit images in GL
{
	this->initializeOpenGLFunctions();
	std::vector<uint8_t> imageData;
	for(auto const &pix : image->imageData)
	{
		IR::vec4<uint8_t> pixel = pix.asRGBAui8();
		imageData.push_back(pixel.r());
		imageData.push_back(pixel.g());
		imageData.push_back(pixel.b());
		if(image->colorFormat == PNG::COLOR_FMT_RGBA) imageData.push_back(pixel.a());
	}
	this->glCreateTextures(GL_TEXTURE_2D, 1, &this->handle);
	this->glTextureStorage2D(this->handle, 1, image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB8 : GL_RGBA8, image->width, image->height);
	this->glTextureSubImage2D(this->handle, 0, 0, 0, image->width, image->height, image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
	//this->glTextureSubImage2D(this->handle, 0, 0, 0, image->width, image->height, image->colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_SHORT, imageData.data()); //TODO enable for 16 bit
	this->glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	this->glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	this->filePath = image->filePath;
	this->width = image->width;
	this->height = image->height;
	this->colorFormat = image->colorFormat;
	this->bitDepth = image->bitDepth;
}

Texture::Texture(Image &image) //TODO handle 16 bit images in GL
{
	this->initializeOpenGLFunctions();
	std::vector<uint8_t> imageData;
	for(auto const &pix : image.imageData)
	{
		IR::vec4<uint8_t> pixel = pix.asRGBAui8();
		imageData.push_back(pixel.r());
		imageData.push_back(pixel.g());
		imageData.push_back(pixel.b());
		if(image.colorFormat == PNG::COLOR_FMT_RGBA) imageData.push_back(pixel.a());
	}
	this->glCreateTextures(GL_TEXTURE_2D, 1, &this->handle);
	this->glTextureStorage2D(this->handle, 1, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB8 : GL_RGBA8, image.width, image.height);
	this->glTextureSubImage2D(this->handle, 0, 0, 0, image.width, image.height, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
	//this->glTextureSubImage2D(this->handle, 0, 0, 0, image.width, image.height, image.colorFormat == PNG::COLOR_FMT_RGB ? GL_RGB : GL_RGBA, GL_UNSIGNED_SHORT, imageData.data()); //TODO enable for 16 bit
	this->glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	this->glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	this->filePath = image.filePath;
	this->width = image.width;
	this->height = image.height;
	this->colorFormat = image.colorFormat;
	this->bitDepth = image.bitDepth;
}

Texture::~Texture()
{
	this->glDeleteTextures(1, &this->handle);
}

void Texture::use(uint32_t target)
{
	this->glBindTextureUnit(target, this->handle);
}
