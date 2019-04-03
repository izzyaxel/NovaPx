#include "io.hh"
#include "util.hh"

#include <png.h>

void pngErrorCallback(png_structp, png_const_charp error)
{
	printf("%s\n", error);
}

PNG readPNG(std::string const &filePath)
{
	FILE *input = fopen(filePath.data(), "rb");
	if(!input)
	{
		printf("PNG Decoder: Unable to open %s for reading\n", filePath.data());
		return {0, 0, 0, 0, nullptr};
	}
	
	unsigned char **imageData = nullptr;
	png_structp pngPtr;
	png_infop infoPtr;
	png_byte header[8];
	fread(header, 8, 1, input);
	
	if(png_sig_cmp(header, 0, 8) != 0)
	{
		printf("PNG Decoder: File %s is not PNG format\n", filePath.data());
		return {0, 0, 0, 0, nullptr};
	}
	
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, pngErrorCallback, nullptr);
	if(pngPtr == nullptr)
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
		printf("PNG Decoder: Failed to create PNG read struct\n");
		return {0, 0, 0, 0, nullptr};
	}
	
	png_set_error_fn(pngPtr, png_get_error_ptr(pngPtr), [](png_structp, png_const_charp){}, [](png_structp, png_const_charp){});
	infoPtr = png_create_info_struct(pngPtr);
	
	if(!infoPtr)
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
		printf("PNG Decoder: Failed to create PNG info struct\n");
		return {0, 0, 0, 0, nullptr};
	}
	
	if(setjmp(png_jmpbuf(pngPtr)))
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
		printf("PNG Decoder: Error during PNG read struct initialization\n");
		return {0, 0, 0, 0, nullptr};
	}
	
	png_init_io(pngPtr, input);
	png_set_sig_bytes(pngPtr, 8);
	png_read_info(pngPtr, infoPtr);
	uint32_t width, height;
	char colorType, bitDepth;
	width = png_get_image_width(pngPtr, infoPtr);
	height = png_get_image_height(pngPtr, infoPtr);
	colorType = png_get_color_type(pngPtr, infoPtr);
	bitDepth = png_get_bit_depth(pngPtr, infoPtr);
	
	if(colorType & PNG_COLOR_MASK_PALETTE)
	{
		printf("PNG Decoder: Paletted PNG files are not currently supported\n");
		return {0, 0, 0, 0, nullptr};
	}
	
	png_set_interlace_handling(pngPtr);
	png_read_update_info(pngPtr, infoPtr);
	
	if(setjmp(png_jmpbuf(pngPtr)))
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
		printf("PNG Decoder: Failed to read PNG\n");
		return {0, 0, 0, 0, nullptr};
	}
	
	imageData = new png_bytep[height * sizeof(png_bytep)];
	
	for(uint32_t i = 0; i < height; i++) imageData[i] = new png_byte[png_get_rowbytes(pngPtr, infoPtr)];
	
	png_read_image(pngPtr, reinterpret_cast<png_bytepp>(imageData));
	png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
	
	fclose(input);
	
	return PNG{width, height, colorType, bitDepth, std::move(imageData)};
}

void writePNG(std::string const &filePath, PNG &image)
{
	writePNG(filePath, image.width, image.height, image.imageData);
}
