#pragma once

constexpr char const *defaultVertSource = R"(
#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv_in;
out vec2 uv;
uniform mat4 mvp;

void main()
{
	uv = uv_in;
	gl_Position = mvp * vec4(pos, 1.0f);
})";

// Draw the canvas and transparency grid
constexpr char const *defaultFragSource = R"(
#version 450

in vec2 uv;
layout(binding = 0) uniform sampler2D tex;
out vec4 fragColor;

uniform uint gridSize = 2;
uniform vec3 color1;
uniform vec3 color2;

vec4 getGridColor()
{
	vec4 color = vec4(color1, 1.0);
	vec2 pos = gl_FragCoord.xy / gridSize;
	ivec2 iPos = ivec2(int(floor(pos.x)), int(floor(pos.y)));
	if((iPos.x + iPos.y) % 2 == 1) color = vec4(color2, 1.0);
	return color;
}

void main()
{
	vec4 canvas = texture(tex, uv);
	fragColor = mix(getGridColor(), canvas, canvas.a);
})";
