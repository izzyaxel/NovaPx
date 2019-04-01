#pragma once

#include <iris/mat4.hh>
#include "../util/def.hh"
#include "color.hh"
#include "fbo.hh"
#include "image.hh"
#include "camera.hh"

#include <iris/vec2.hh>
#include <cstdint>

struct Renderer
{
	Renderer();
	~Renderer();
	
	void render(Image &canvas, Camera &camera);
	void onResize(uint32_t width, uint32_t height);

private:
	uint32_t contextWidth, contextHeight;
	Color clearColor;
	IR::mat4x4<float> m, v, p, mvp;
};
