#include "util/window.hh"
#include "util/util.hh"
#include "graphics/camera.hh"

#include <string>
#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

long long unsigned int ticks = 0;
uint32_t windowWidth = 800, windowHeight = 600;
uint32_t majorVersion = 1, minorVersion  = 0, bugfixVersion = 0;
std::string windowName = "PixelCreator | " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(bugfixVersion);
bool exiting = false;

UP<Window> window;
Image canvas;
Camera camera;

int main()
{
	//setup
	window = MU<Window>(windowWidth, windowHeight, windowWidth, windowHeight, windowName, true, true);
	
	//bind keys
	Input::bindTriggerModeKey(Keys::KEY_ESC, [&] (bool down)
	{
		if(!down) exiting = true;
	});
	Input::bindTriggerModeKey(Keys::KEY_F12, [&] (bool down)
	{
		if(!down) window->takeScreenshot(getCWD() + "screenshots/");
	});
	
	//register event handlers
	window->eventBus->registerEventHandler<Event::WINDOWSIZECHANGED>([&] ()
	{
		int32_t w = 0, h = 0;
		SDL_GL_GetDrawableSize(reinterpret_cast<SDL_Window*>(window->window), &w, &h);
		window->onResize(static_cast<uint32_t>(w), static_cast<uint32_t>(h));
	});
	window->eventBus->registerEventHandler<Event::MOUSEBUTTON, bool, uint8_t>([&] (bool down, uint8_t button)
	{
		switch(button)
		{
			case 1: //LMB
	
				break;
	
			case 2: //MMB
	
				break;
	
			case 3: //RMB
	
				break;
	
			default: break;
	    }
	});
	window->eventBus->registerEventHandler<Event::KEYBOARD, bool, SDL_KeyboardEvent>([&] (bool down, SDL_KeyboardEvent event)
	{
		for(auto &bind : Input::triggerModeKeybinds) if(static_cast<int>(event.keysym.scancode) == static_cast<int>(bind.key)) bind.callback(down);
	});
	
	//enter main loop
	SDL_Event event;
	do
	{
		Input::updateImmediateModeKbd();
		while(SDL_PollEvent(&event) != 0)
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP: window->eventBus->post<Event::MOUSEBUTTON>(false, event.button.button); break;
				case SDL_MOUSEBUTTONDOWN: window->eventBus->post<Event::MOUSEBUTTON>(true, event.button.button); break;
				case SDL_KEYDOWN: window->eventBus->post<Event::KEYBOARD>(true, event.key); break;
				case SDL_KEYUP: window->eventBus->post<Event::KEYBOARD>(false, event.key); break;
				case SDL_QUIT: exiting = true; break; //Event is posted when the engine actually starts shutting down
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_CLOSE) window->eventBus->post<Event::WINDOWCLOSE>();
					if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) window->eventBus->post<Event::WINDOWFOCUSGAINED>();
					if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) window->eventBus->post<Event::WINDOWFOCUSLOST>();
					if(event.window.event == SDL_WINDOWEVENT_TAKE_FOCUS) window->eventBus->post<Event::WINDOWTAKEFOCUS>();
					if(event.window.event == SDL_WINDOWEVENT_ENTER) window->eventBus->post<Event::WINDOWENTER>();
					if(event.window.event == SDL_WINDOWEVENT_LEAVE) window->eventBus->post<Event::WINDOWLEAVE>();
					if(event.window.event == SDL_WINDOWEVENT_EXPOSED) window->eventBus->post<Event::WINDOWEXPOSED>();
					if(event.window.event == SDL_WINDOWEVENT_HIDDEN) window->eventBus->post<Event::WINDOWHIDDEN>();
					if(event.window.event == SDL_WINDOWEVENT_SHOWN) window->eventBus->post<Event::WINDOWSHOWN>();
					if(event.window.event == SDL_WINDOWEVENT_HIT_TEST) window->eventBus->post<Event::WINDOWHITTEST>();
					if(event.window.event == SDL_WINDOWEVENT_RESTORED) window->eventBus->post<Event::WINDOWRESTORED>();
					if(event.window.event == SDL_WINDOWEVENT_MINIMIZED) window->eventBus->post<Event::WINDOWMINIMIZED>();
					if(event.window.event == SDL_WINDOWEVENT_MAXIMIZED) window->eventBus->post<Event::WINDOWMAXIMIZED>();
					if(event.window.event == SDL_WINDOWEVENT_MOVED) window->eventBus->post<Event::WINDOWMOVED>();
					if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || event.window.event == SDL_WINDOWEVENT_RESIZED) window->eventBus->post<Event::WINDOWSIZECHANGED>();
					break;
				default: break;
			}
			
			//TODO update UI
			window->render(canvas, camera);
		}
		SDL_Delay(1);
	} while(!exiting);
	//cleanup
	//TODO check if canvas has been saved, ask if it hasn't
	window->eventBus->post<Event::EXITING>();
	window.reset();
	return 0;
}
