#include "color.hh"
#include "../util/util.hh"

Color Color::operator+(Color const &other)
{
	Color out;
	out.data.r() = this->data.r() + other.data.r();
	out.data.g() = this->data.g() + other.data.g();
	out.data.b() = this->data.b() + other.data.b();
	out.data.a() = this->data.a() + other.data.a();
	return out;
}

Color Color::operator-(Color const &other)
{
	Color out;
	out.data.r() = this->data.r() - other.data.r();
	out.data.g() = this->data.g() - other.data.g();
	out.data.b() = this->data.b() - other.data.b();
	out.data.a() = this->data.a() - other.data.a();
	return out;
}

Color Color::operator*(Color const &other)
{
	Color out;
	out.data.r() = this->data.r() * other.data.r();
	out.data.g() = this->data.g() * other.data.g();
	out.data.b() = this->data.b() * other.data.b();
	out.data.a() = this->data.a() * other.data.a();
	return out;
}

Color Color::operator/(Color const &other)
{
	Color out;
	out.data.r() = this->data.r() / other.data.r();
	out.data.g() = this->data.g() / other.data.g();
	out.data.b() = this->data.b() / other.data.b();
	out.data.a() = this->data.a() / other.data.a();
	return out;
}

bool Color::operator==(Color const &other)
{
	return this->data.r() == other.data.r() && this->data.g() == other.data.g() && this->data.b() == other.data.b() && this->data.a() == other.data.a();
}

bool Color::operator!=(Color const &other)
{
	return ! this->operator==(other);
}

void Color::fromRGBf(float r, float g, float b)
{
	this->data.r() = static_cast<iFmt>(bound<float>(r, 0.0f, 1.0f) * ui16Max);
	this->data.g() = static_cast<iFmt>(bound<float>(g, 0.0f, 1.0f) * ui16Max);
	this->data.b() = static_cast<iFmt>(bound<float>(b, 0.0f, 1.0f) * ui16Max);
}

void Color::fromRGBAf(float r, float g, float b, float a)
{
	this->data.r() = static_cast<iFmt>(bound<float>(r, 0.0f, 1.0f) * ui16Max);
	this->data.g() = static_cast<iFmt>(bound<float>(g, 0.0f, 1.0f) * ui16Max);
	this->data.b() = static_cast<iFmt>(bound<float>(b, 0.0f, 1.0f) * ui16Max);
	this->data.a() = static_cast<iFmt>(bound<float>(a, 0.0f, 1.0f) * ui16Max);
}

void Color::fromRGBui8(uint8_t r, uint8_t g, uint8_t b)
{
	this->data.r() = static_cast<iFmt>(r * 256);
	this->data.g() = static_cast<iFmt>(g * 256);
	this->data.b() = static_cast<iFmt>(b * 256);
}

void Color::fromRGBAui8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->data.r() = static_cast<iFmt>(r * 256);
	this->data.g() = static_cast<iFmt>(g * 256);
	this->data.b() = static_cast<iFmt>(b * 256);
	this->data.a() = static_cast<iFmt>(a * 256);
}

void Color::fromRGBui16(uint16_t r, uint16_t g, uint16_t b)
{
	this->data.r() = r;
	this->data.g() = g;
	this->data.b() = b;
}

void Color::fromRGBAui16(uint16_t r, uint16_t g, uint16_t b, uint16_t a)
{
	this->data.r() = r;
	this->data.g() = g;
	this->data.b() = b;
	this->data.a() = a;
}

void Color::fromHex(uint32_t hex)
{
	this->data.a() = static_cast<iFmt>(((hex & 0xFF000000) >> 24) * 256);
	this->data.r() = static_cast<iFmt>(((hex & 0x00FF0000) >> 16) * 256);
	this->data.g() = static_cast<iFmt>(((hex & 0x0000FF00) >> 8) * 256);
	this->data.b() = static_cast<iFmt>((hex & 0x000000FF) * 256);
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
			this->data.b() = static_cast<iFmt>((conv & 0x00F) * 256);
			this->data.g() = static_cast<iFmt>((conv & 0x0F0 << 4) * 256);
			this->data.r() = static_cast<iFmt>((conv & 0xF00 << 8) * 256);
			break;
		case 5:
			this->data.a() = static_cast<iFmt>((conv & 0x000F) * 256);
			this->data.b() = static_cast<iFmt>((conv & 0x00F0 << 4) * 256);
			this->data.g() = static_cast<iFmt>((conv & 0x0F00 << 8) * 256);
			this->data.r() = static_cast<iFmt>((conv & 0xF000 << 12) * 256);
			break;
		case 7:
			this->data.r() = static_cast<iFmt>((conv & 0xFF000000 << 16) * 256);
			this->data.g() = static_cast<iFmt>((conv & 0xFF000000 << 8) * 256);
			this->data.b() = static_cast<iFmt>((conv & 0xFF000000) * 256);
			break;
		case 9:
			this->data.r() = static_cast<iFmt>((conv & 0xFF000000 << 24) * 256);
			this->data.g() = static_cast<iFmt>((conv & 0xFF000000 << 16) * 256);
			this->data.b() = static_cast<iFmt>((conv & 0xFF000000 << 8) * 256);
			this->data.a() = static_cast<iFmt>((conv & 0xFF000000) * 256);
			break;
	}
}

vec3<float> Color::asRGBf() const
{
	return {static_cast<float>(this->data.r()) / ui16Max, static_cast<float>(this->data.g()) / ui16Max, static_cast<float>(this->data.b()) / ui16Max};
}

vec4<float> Color::asRGBAf() const
{
	return {static_cast<float>(this->data.r()) / ui16Max, static_cast<float>(this->data.g()) / ui16Max, static_cast<float>(this->data.b()) / ui16Max, static_cast<float>(this->data.a()) / ui16Max};
}

vec3<uint8_t> Color::asRGBui8() const
{
	return {static_cast<uint8_t>(this->data.r() / 256), static_cast<uint8_t>(this->data.g() / 256), static_cast<uint8_t>(this->data.b() / 256)};
}

vec4<uint8_t> Color::asRGBAui8() const
{
	return {static_cast<uint8_t>(this->data.r() / 256), static_cast<uint8_t>(this->data.g() / 256), static_cast<uint8_t>(this->data.b() / 256), static_cast<uint8_t>(this->data.a() / 256)};
}

vec3<uint16_t> Color::asRGBui16() const
{
	return {this->data.r(), this->data.g(), this->data.b()};
}

vec4<uint16_t> Color::asRGBAui16() const
{
	return {this->data.r(), this->data.g(), this->data.b(), this->data.a()};
}

uint32_t Color::asHex() const
{
	return static_cast<uint8_t>(this->data.a() / 256) << 24 | static_cast<uint8_t>(this->data.r() / 256) << 16 | static_cast<uint8_t>(this->data.g() / 256) << 8 | static_cast<uint8_t>(this->data.b() / 256);
}

std::string Color::asWeb() const
{
	std::stringstream ss;
	ss << std::hex << (static_cast<uint8_t>(this->data.r() / 256) << 24 | static_cast<uint8_t>(this->data.g() / 256) << 16 | static_cast<uint8_t>(this->data.b() / 256) << 8 | static_cast<uint8_t>(this->data.a() / 256));
	std::string ssc = ss.str();
	return std::string{"#"} + ssc;
}

void Color::print()
{
	printf("R: %u G: %u B: %u A: %u\n", this->data.r(), this->data.g(), this->data.b(), this->data.a());
}
