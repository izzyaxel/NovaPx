#pragma once

#include "../graphics/png.hh"
#include "../graphics/image.hh"

PNG readPNG(std::string const &filePath);
void writePNG(std::string const &filePath, PNG &image);
void writePNG(std::string const &filePath, Image &image);
void writeScreenshot(std::string const &folderPath, uint32_t width, uint32_t height);

//TODO GIF support
