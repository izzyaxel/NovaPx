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

constexpr char const *defaultFragSource = R"(
#version 450

in vec2 uv;
layout(binding = 0) uniform sampler2D tex;
out vec4 fragColor;

void main()
{
	fragColor = texture(tex, uv);
})";

constexpr char const *textFragSource = R"(
#version 450

in vec2 uv;
uniform vec4 inputColor;
layout(binding = 0) uniform sampler2D tex;
out vec4 fragColor;

void main()
{
	fragColor = vec4(inputColor.xyz, texture(tex, uv).x * inputColor.w);
})";

constexpr char const *transferVertSource = R"(
#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv_in;
out vec2 uv;

void main()
{
	uv = uv_in;
	gl_Position = vec4(pos, 1.0f);
})";

constexpr char const *transferFragSource = R"(
#version 450

in vec2 uv;
layout(binding = 0) uniform sampler2D tex;
out vec4 fragColor;

void main()
{
	fragColor = texture(tex, uv);
})";
