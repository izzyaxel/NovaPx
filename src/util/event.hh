#pragma once

#include <functional>
#include <SDL2/SDL_events.h>

enum struct Event
{
	EXITING,
	MOUSEBUTTON, KEYBOARD,
	WINDOWCLOSE, WINDOWSIZECHANGED, WINDOWFOCUSGAINED, WINDOWFOCUSLOST, WINDOWENTER, WINDOWLEAVE, WINDOWEXPOSED, WINDOWHIDDEN,
	WINDOWSHOWN, WINDOWHITTEST, WINDOWRESTORED, WINDOWMINIMIZED, WINDOWMAXIMIZED, WINDOWTAKEFOCUS, WINDOWMOVED,
};

struct EventBus
{
	template <Event e, typename... Args> void post(Args ...args)
	{
		if constexpr(e == Event::EXITING) for(auto const &cb : this->exitingEventCBs) cb();
		else if constexpr(e == Event::WINDOWCLOSE) for(auto const &cb : this->windowCloseEventCBs) cb();
		else if constexpr(e == Event::WINDOWSIZECHANGED) for(auto const &cb : this->windowSizeChangedEventCBs) cb();
		else if constexpr(e == Event::WINDOWFOCUSGAINED) for(auto const &cb : this->windowFocusGainedEventCBs) cb();
		else if constexpr(e == Event::WINDOWFOCUSLOST) for(auto const &cb : this->windowFocusLostEventCBs) cb();
		else if constexpr(e == Event::WINDOWENTER) for(auto const &cb : this->windowEnterEventCBs) cb();
		else if constexpr(e == Event::WINDOWLEAVE) for(auto const &cb : this->windowLeaveEventCBs) cb();
		else if constexpr(e == Event::WINDOWEXPOSED) for(auto const &cb : this->windowExposedEventCBs) cb();
		else if constexpr(e == Event::WINDOWHIDDEN) for(auto const &cb : this->windowHiddenEventCBs) cb();
		else if constexpr(e == Event::WINDOWSHOWN) for(auto const &cb : this->windowShownEventCBs) cb();
		else if constexpr(e == Event::WINDOWHITTEST) for(auto const &cb : this->windowHitTestEventCBs) cb();
		else if constexpr(e == Event::WINDOWRESTORED) for(auto const &cb : this->windowRestoredEventCBs) cb();
		else if constexpr(e == Event::WINDOWMINIMIZED) for(auto const &cb : this->windowMinimizedEventCBs) cb();
		else if constexpr(e == Event::WINDOWMAXIMIZED) for(auto const &cb : this->windowMaximizedEventCBs) cb();
		else if constexpr(e == Event::WINDOWTAKEFOCUS) for(auto const &cb : this->windowTakeFocusEventCBs) cb();
		else if constexpr(e == Event::WINDOWMOVED) for(auto const &cb : this->windowMovedEventCBs) cb();
		else if constexpr(e == Event::MOUSEBUTTON) for(auto const &cb : this->mouseButtonEventCBs) cb(args...);
		else if constexpr(e == Event::KEYBOARD) for(auto const &cb : this->keyEventCBs) cb(args...);
	}
	
	template <Event e, typename... Args, typename Callback = std::function<void(Args ...)>> void registerEventHandler(Callback callback)
	{
		if constexpr(e == Event::EXITING) this->exitingEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWCLOSE) this->windowCloseEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWSIZECHANGED) this->windowSizeChangedEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWFOCUSGAINED) this->windowFocusGainedEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWFOCUSLOST) this->windowFocusLostEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWENTER) this->windowEnterEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWLEAVE) this->windowLeaveEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWEXPOSED) this->windowExposedEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWHIDDEN) this->windowHiddenEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWSHOWN) this->windowShownEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWHITTEST) this->windowHitTestEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWRESTORED) this->windowRestoredEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWMINIMIZED) this->windowMinimizedEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWMAXIMIZED) this->windowMaximizedEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWTAKEFOCUS) this->windowTakeFocusEventCBs.push_back(callback);
		else if constexpr(e == Event::WINDOWMOVED) this->windowMovedEventCBs.push_back(callback);
		else if constexpr(e == Event::MOUSEBUTTON) this->mouseButtonEventCBs.push_back(callback);
		else if constexpr(e == Event::KEYBOARD) this->keyEventCBs.push_back(callback);
	}

private:
	std::vector<std::function<void ()>> exitingEventCBs,
	windowCloseEventCBs, windowSizeChangedEventCBs, windowFocusGainedEventCBs, windowFocusLostEventCBs, windowEnterEventCBs, windowLeaveEventCBs, windowExposedEventCBs, windowHiddenEventCBs, windowShownEventCBs, windowHitTestEventCBs, windowRestoredEventCBs, windowMinimizedEventCBs, windowMaximizedEventCBs, windowTakeFocusEventCBs, windowMovedEventCBs;
	std::vector<std::function<void (bool down, uint8_t button)>>mouseButtonEventCBs;
	std::vector<std::function<void (bool down, SDL_KeyboardEvent event)>> keyEventCBs;
};
