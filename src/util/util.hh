#pragma once

#include <string>
#include <vector>
#include <limits>

constexpr uint8_t ui8Max = std::numeric_limits<uint8_t>::max();
constexpr uint16_t ui16Max = std::numeric_limits<uint16_t>::max();
constexpr float ui16Maxf = static_cast<float>(std::numeric_limits<uint16_t>::max());

template <typename T> T bound(T val, T lower, T upper)
{
	if(val < lower) return lower;
	if(val > upper) return upper;
	return val;
}

std::string getCWD();
std::string readTextFile(std::string const &filePath);
void createDirectory(std::string const &folderPath);
void screenshot(std::string const &folderPath, uint32_t width, uint32_t height);
void writePNG(std::string const &filePath, uint32_t width, uint32_t height, unsigned char **imageData);

namespace StringTools
{
	bool contains(std::string const &input, std::string const &searchToken);
	bool startsWith(std::string const &input, std::string const &searchToken);
	bool endsWith(std::string const &input, std::string const &searchToken);
	std::string subString(std::string const &input, uint32_t const &distFromStart, uint32_t const &distFromEnd);
	std::string trim(std::string const &input);
	std::string remove(std::string const &input, char const &remove);
	std::string removeMult(std::string const &input, std::vector<char> const &remove);
	std::vector<std::string> split(std::string const &input, char const &splitOn, bool const &removeMatches);
	std::vector<std::string> splitMult(std::string const &input, std::vector<char> const &splitOn, bool const &removeMatches);
	std::vector<std::string> splitSeq(std::string const &input, std::string const &splitOn);
	std::vector<std::string> splitSeqMult(std::string const &input, std::vector<std::string> const &splitOn);
	std::string replaceAll(std::string const &input, char const &searchFor, char const &replaceWith);
}
