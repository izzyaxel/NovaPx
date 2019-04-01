#pragma once

#include <iris/vec2.hh>

struct Camera
{
	IR::vec2<int32_t> pos{};
	uint32_t zoomMult = 1;
};
