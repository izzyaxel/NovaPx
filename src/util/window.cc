#include "window.hh"
#include "../util/def.hh"
#include "input.hh"
#include "event.hh"
#include "util.hh"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glad/glad.h>

void glDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *userParam)
{
	printf("An OpenGL error occured: \nSeverity: ");
	switch(severity)
	{
		case GL_DEBUG_SEVERITY_LOW:
			printf("LOW");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			printf("MEDIUM");
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			printf("HIGH");
			break;
		default: break;
	}
	printf("\nID: %u\nType: ", id);
	switch(type)
	{
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			printf("Deprecated Behavior");
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			printf("Undefined Behavior");
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			printf("Portability");
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			printf("Performance");
			break;
		case GL_DEBUG_TYPE_OTHER:
			printf("Other");
			break;
		default: break;
	}
	printf("\nMessage: %s\n", message);
}

void Window::onResize(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
	this->renderer->onResize(width, height);
}

Window::Window(uint32_t width, uint32_t height, uint32_t minWidth, uint32_t minHeight, std::string const &name, bool resizable, bool startMaximized)
{
	this->eventBus = new EventBus;
	
	this->glMajorVersion = 4;
	this->glMinorVersion = 6;
	this->width = width;
	this->height = height;
	this->windowedWidth = width;
	this->windowedHeight = height;
	this->minWidth = minWidth;
	this->minHeight = minHeight;
	this->name = name;
	this->resizable = resizable;
	this->startMaximized = startMaximized;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow(this->name.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);
	if(!this->window) throw std::runtime_error("Window Setup: Failed to create a window");
	SDL_SetWindowResizable(reinterpret_cast<SDL_Window*>(this->window), this->resizable ? SDL_TRUE : SDL_FALSE);
	if(this->minHeight != 0 && this->minWidth != 0) SDL_SetWindowMinimumSize(reinterpret_cast<SDL_Window*>(this->window), this->minWidth, this->minHeight);
	if(this->startMaximized)
	{
		SDL_MaximizeWindow(reinterpret_cast<SDL_Window*>(this->window));
		int32_t w, h;
		SDL_GL_GetDrawableSize(reinterpret_cast<SDL_Window*>(this->window), &w, &h);
		this->width = static_cast<uint32_t>(w);
		this->height = static_cast<uint32_t>(h);
	}
	Input::init();
	
	SDL_GL_LoadLibrary(nullptr);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	this->context = SDL_GL_CreateContext(reinterpret_cast<SDL_Window*>(window));
	if(!this->context) throw std::runtime_error("Failed to initialize renderer, OpenGL 4.5 is not supported on your hardware");
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	if(!GLAD_GL_VERSION_4_5) throw std::runtime_error("Failed to initialize renderer, OpenGL 4.5 is not supported on your hardware");
	SDL_GL_SetSwapInterval(this->syncMode);
	
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebug, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
	this->renderer = new Renderer;
	initFBOPool(4, width, height);
}

Window::~Window()
{
	delete this->eventBus;
	delete this->renderer;
	SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(this->window));
	SDL_Quit();
}

void Window::setTitle(std::string const &name)
{
	this->name = name;
	SDL_SetWindowTitle(reinterpret_cast<SDL_Window*>(this->window), name.data());
}

void Window::setSize(uint32_t width, uint32_t height)
{
	SDL_SetWindowSize(reinterpret_cast<SDL_Window*>(this->window), width, height);
	this->eventBus->post<Event::WINDOWSIZECHANGED>();
}

void Window::setResizability(bool resizable)
{
	this->resizable = resizable;
	SDL_SetWindowResizable(reinterpret_cast<SDL_Window*>(this->window), resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::maximize()
{
	SDL_MaximizeWindow(reinterpret_cast<SDL_Window*>(this->window));
	this->eventBus->post<Event::WINDOWSIZECHANGED>();
	this->eventBus->post<Event::WINDOWMAXIMIZED>();
}

void Window::minimize()
{
	SDL_MinimizeWindow(reinterpret_cast<SDL_Window*>(this->window));
	this->eventBus->post<Event::WINDOWMINIMIZED>();
}

void Window::takeScreenshot(std::string const &screenshotDir)
{
	screenshot(screenshotDir, this->width, this->height);
}

void Window::render(Image &canvas, Camera &camera)
{
	this->renderer->render(canvas, camera);
	SDL_GL_SwapWindow(reinterpret_cast<SDL_Window*>(this->window));
}
