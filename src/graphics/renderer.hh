#pragma once

#include <iris/mat4.hh>
#include "../util/def.hh"
#include "color.hh"
#include "fbo.hh"
#include "image.hh"

#include <iris/vec2.hh>
#include <cstdint>
#include <QtGui/QOpenGLFunctions_4_5_Core>

struct Renderer
{
	Renderer(QOpenGLFunctions_4_5_Core *funcs);
	~Renderer();
	
	void render(QOpenGLFunctions_4_5_Core *funcs);
	void onResize(QOpenGLFunctions_4_5_Core *funcs);
	void screenshot(std::string const &folderPath, uint32_t width, uint32_t height, QOpenGLFunctions_4_5_Core *funcs);

private:
	Color clearColor;
	IR::mat4x4<float> m, v, p, mvp;
};
