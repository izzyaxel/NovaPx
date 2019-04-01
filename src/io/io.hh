#pragma once

#include "../graphics/png.hh"

PNG readPNG(std::string const &filePath);
void writePNG(std::string const &filePath, PNG &image);
void writeScreenshot(std::string const &folderPath, uint32_t width, uint32_t height);

//TODO GIF support
