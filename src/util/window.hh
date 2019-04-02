#pragma once

#include "event.hh"
#include "../graphics/renderer.hh"

#include <cstdint>
#include <string>

struct Window
{
	Window(uint32_t width, uint32_t height, uint32_t minWidth, uint32_t minHeight, std::string const &name, bool resizable, bool startMaximized);
	~Window();
	
	void setTitle(std::string const &name);
	void setSize(uint32_t width, uint32_t height);
	void setResizability(bool resizable);
	void maximize();
	void minimize();
	void onResize(uint32_t width, uint32_t height);
	void takeScreenshot(std::string const &screenshotDir);
	
	void render(Image &canvas, Camera &camera);
	
	void *window = nullptr, *context = nullptr;
	uint8_t glMajorVersion = 4, glMinorVersion = 5;
	int8_t syncMode = 0;
	uint32_t width = 800, height, minWidth, minHeight, fullscreenWidth, fullscreenHeight, windowedWidth, windowedHeight, updateRate = 60, defaultUpdateRate = 60, minFPS = 60;
	std::string name = "";
	bool resizable = true, startMaximized = false, vsyncOn = false;
	
	Renderer *renderer;
	EventBus *eventBus;
};
