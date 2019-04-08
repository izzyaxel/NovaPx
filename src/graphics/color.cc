#include "color.hh"
#include "../util/util.hh"

Color Color::operator+(Color const &other)
{
	Color out;
	out.r = this->r + other.r;
	out.g = this->g + other.g;
	out.b = this->b + other.b;
	out.a = this->a + other.a;
	return out;
}

bool Color::operator==(Color const &other)
{
	return this->r == other.r && this->g == other.g && this->b == other.b && this->a == other.a;
}

void Color::fromRGBf(float r, float g, float b)
{
	this->r = static_cast<iFmt>(bound<float>(r, 0.0f, 1.0f) * ui16Max);
	this->g = static_cast<iFmt>(bound<float>(g, 0.0f, 1.0f) * ui16Max);
	this->b = static_cast<iFmt>(bound<float>(b, 0.0f, 1.0f) * ui16Max);
}

void Color::fromRGBAf(float r, float g, float b, float a)
{
	this->r = static_cast<iFmt>(bound<float>(r, 0.0f, 1.0f) * ui16Max);
	this->g = static_cast<iFmt>(bound<float>(g, 0.0f, 1.0f) * ui16Max);
	this->b = static_cast<iFmt>(bound<float>(b, 0.0f, 1.0f) * ui16Max);
	this->a = static_cast<iFmt>(bound<float>(a, 0.0f, 1.0f) * ui16Max);
}

void Color::fromRGBui8(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = static_cast<iFmt>(r * 256);
	this->g = static_cast<iFmt>(g * 256);
	this->b = static_cast<iFmt>(b * 256);
}

void Color::fromRGBAui8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->r = static_cast<iFmt>(r * 256);
	this->g = static_cast<iFmt>(g * 256);
	this->b = static_cast<iFmt>(b * 256);
	this->a = static_cast<iFmt>(a * 256);
}

void Color::fromRGBui16(uint16_t r, uint16_t g, uint16_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Color::fromRGBAui16(uint16_t r, uint16_t g, uint16_t b, uint16_t a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::fromHex(uint32_t hex)
{
	this->a = static_cast<iFmt>(((hex & 0xFF000000) >> 24) * 256);
	this->r = static_cast<iFmt>(((hex & 0x00FF0000) >> 16) * 256);
	this->g = static_cast<iFmt>(((hex & 0x0000FF00) >> 8) * 256);
	this->b = static_cast<iFmt>((hex & 0x000000FF) * 256);
}

void Color::fromWeb(std::string const &color)
{
	if(color.empty() || color[0] != '#')
	{
		printf("Invalid color formatting\n");
		return;
	}
	uint32_t conv = static_cast<uint32_t>(std::strtol(color.data() + 1, nullptr, 16));
	switch(color.size())
	{
		default: printf("Invalid color formatting\n"); break;
		case 4:
			this->b = static_cast<iFmt>((conv & 0x00F) * 256);
			this->g = static_cast<iFmt>((conv & 0x0F0 << 4) * 256);
			this->r = static_cast<iFmt>((conv & 0xF00 << 8) * 256);
			break;
		case 5:
			this->a = static_cast<iFmt>((conv & 0x000F) * 256);
			this->b = static_cast<iFmt>((conv & 0x00F0 << 4) * 256);
			this->g = static_cast<iFmt>((conv & 0x0F00 << 8) * 256);
			this->r = static_cast<iFmt>((conv & 0xF000 << 12) * 256);
			break;
		case 7:
			this->r = static_cast<iFmt>((conv & 0xFF000000 << 16) * 256);
			this->g = static_cast<iFmt>((conv & 0xFF000000 << 8) * 256);
			this->b = static_cast<iFmt>((conv & 0xFF000000) * 256);
			break;
		case 9:
			this->r = static_cast<iFmt>((conv & 0xFF000000 << 24) * 256);
			this->g = static_cast<iFmt>((conv & 0xFF000000 << 16) * 256);
			this->b = static_cast<iFmt>((conv & 0xFF000000 << 8) * 256);
			this->a = static_cast<iFmt>((conv & 0xFF000000) * 256);
			break;
	}
}

IR::vec3<float> Color::asRGBf() const
{
	return {static_cast<float>(this->r) / ui16Max, static_cast<float>(this->g) / ui16Max, static_cast<float>(this->b) / ui16Max};
}

IR::vec4<float> Color::asRGBAf() const
{
	return {static_cast<float>(this->r) / ui16Max, static_cast<float>(this->g) / ui16Max, static_cast<float>(this->b) / ui16Max, static_cast<float>(this->a) / ui16Max};
}

IR::vec3<uint8_t> Color::asRGBui8() const
{
	return {static_cast<uint8_t>(this->r / 256), static_cast<uint8_t>(this->g / 256), static_cast<uint8_t>(this->b / 256)};
}

IR::vec4<uint8_t> Color::asRGBAui8() const
{
	return {static_cast<uint8_t>(this->r / 256), static_cast<uint8_t>(this->g / 256), static_cast<uint8_t>(this->b / 256), static_cast<uint8_t>(this->a / 256)};
}

IR::vec3<uint16_t> Color::asRGBui16() const
{
	return {this->r, this->g, this->b};
}

IR::vec4<uint16_t> Color::asRGBAui16() const
{
	return {this->r, this->g, this->b, this->a};
}

uint32_t Color::asHex() const
{
	return static_cast<uint8_t>(this->a / 256) << 24 | static_cast<uint8_t>(this->r / 256) << 16 | static_cast<uint8_t>(this->g / 256) << 8 | static_cast<uint8_t>(this->b / 256);
}

std::string Color::asWeb() const
{
	std::stringstream ss;
	ss << std::hex << (static_cast<uint8_t>(this->r / 256) << 24 | static_cast<uint8_t>(this->g / 256) << 16 | static_cast<uint8_t>(this->b / 256) << 8 | static_cast<uint8_t>(this->a / 256));
	return "#" + ss.str();
}
