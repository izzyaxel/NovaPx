#include "globals.hh"

UP<EventBus> eventBus;
SP<Image> canvas;
SP<Camera> camera;

namespace Info
{
	bool exiting = false, screenshotQueued = false;
	std::string screenshotDir;
}

namespace Mouse
{
	bool lmbDown = false, rmbDown = false, mmbDown = false;
	bool lmbDownDrag = false, rmbDownDrag = false, mmbDownDrag = false;
	IR::vec2<int32_t> pos, prevPos, lastClickPos, lastReleasePos;
}

namespace Keyboard
{
	bool spaceDown;
}

namespace Context
{
	uint32_t width = 0, height = 0;
}
