#pragma once

#include "def.hh"
#include "../graphics/image.hh"
#include "tools.hh"

#include <iris/vec2.hh>

extern SP<Image> canvas; //TODO move to in-place editing on the GPU

namespace Info
{
	extern uint32_t majorVersion, minorVersion, bugfixVersion;
	extern std::string windowName;
	extern bool exiting, screenshotQueued;
	extern std::string screenshotDir;
}

namespace Mouse
{
	extern bool lmbDown, rmbDown, mmbDown;
	extern bool lmbDownDrag, rmbDownDrag, mmbDownDrag;
	extern IR::vec2<int32_t> pos, prevPos, lastClickPos, lastReleasePos;
}

namespace Keyboard
{
	extern bool spaceDown;
}

namespace Camera
{
	extern IR::vec2<int32_t> pos;
	extern int32_t minZoom, maxZoom;
}

namespace Context
{
	extern uint32_t width, height;
}

namespace State
{
	extern Color curColor, eraserColor, transparencyGridColor1, transparencyGridColor2;
	extern uint8_t gridSize;
	extern Tools tool;
}
