#pragma once

#include "event.hh"
#include "def.hh"
#include "../graphics/image.hh"
#include "../graphics/camera.hh"

#include <iris/vec2.hh>

extern UP<EventBus> eventBus;
extern SP<Image> canvas;
extern SP<Camera> camera;

namespace Info
{
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

namespace Context
{
	extern uint32_t width, height;
}
