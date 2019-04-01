#pragma once

#if __has_include("glm/glm.hpp")
#include "vec2.hh"
#include "vec3.hh"
#include "vec4.hh"
#include "mat3.hh"
#include "mat4.hh"

namespace Iris
{
	//iris to glm
	template <typename T> glm::vec2 IRtoGLMvec2(vec2<T> const &in)
	{
		glm::vec2 out = glm::vec2{in[0], in[1]};
		return out;
	}
	
	template <typename T> glm::vec3 IRtoGLMvec3(vec3<T> const &in)
	{
		glm::vec3 out = glm::vec3{in[0], in[1], in[2]};
		return out;
	}
	
	template <typename T> glm::vec4 IRtoGLMvec4(vec4<T> const &in)
	{
		glm::vec4 out = glm::vec4{in[0], in[1], in[2], in[3]};
		return out;
	}
	
	template <typename T> glm::mat3x3 IRtoGLMmat3(mat3x3<T> const &in)
	{
		glm::mat3x3 out;
		out[0][0] = in[0][0];
		out[0][1] = in[0][1];
		out[0][2] = in[0][2];
		out[1][0] = in[1][0];
		out[1][1] = in[1][1];
		out[1][2] = in[1][2];
		out[2][0] = in[2][0];
		out[2][1] = in[2][1];
		out[2][2] = in[2][2];
		return out;
	}
	
	template <typename T> glm::mat4x4 IRtoGLMmat4(mat4x4<T> const &in)
	{
		glm::mat4x4 out;
		out[0][0] = in[0][0];
		out[0][1] = in[0][1];
		out[0][2] = in[0][2];
		out[0][3] = in[0][3];
		out[1][0] = in[1][0];
		out[1][1] = in[1][1];
		out[1][2] = in[1][2];
		out[1][3] = in[1][3];
		out[2][0] = in[2][0];
		out[2][1] = in[2][1];
		out[2][2] = in[2][2];
		out[2][3] = in[2][3];
		out[3][0] = in[3][0];
		out[3][1] = in[3][1];
		out[3][2] = in[3][2];
		out[3][3] = in[3][3];
		return out;
	}
	
	//glm to iris
	template <typename T> vec2<T> GLMtoIRvec2(glm::vec2 const &in)
	{
		vec2<T> out = {in[0], in[1]};
		return out;
	}
	
	template <typename T> vec3<T> GLMtoIRvec3(glm::vec3 const &in)
	{
		vec3<T> out = {in[0], in[1], in[2]};
		return out;
	}
	
	template <typename T> vec4<T> GLMtoIRvec4(glm::vec4 const &in)
	{
		vec4<T> out = {in[0], in[1], in[2], in[3]};
		return out;
	}
	
	template <typename T> mat3x3<T> GLMtoIRmat3(glm::mat3x3 const &in)
	{
		mat3x3<T> out;
		out[0][0] = in[0][0];
		out[0][1] = in[0][1];
		out[0][2] = in[0][2];
		out[1][0] = in[1][0];
		out[1][1] = in[1][1];
		out[1][2] = in[1][2];
		out[2][0] = in[2][0];
		out[2][1] = in[2][1];
		out[2][2] = in[2][2];
		return out;
	}
	
	template <typename T> mat4x4<T> GLMtoIRmat4(glm::mat4x4 const &in)
	{
		mat4x4<T> out;
		out[0][0] = in[0][0];
		out[0][1] = in[0][1];
		out[0][2] = in[0][2];
		out[0][3] = in[0][3];
		out[1][0] = in[1][0];
		out[1][1] = in[1][1];
		out[1][2] = in[1][2];
		out[1][3] = in[1][3];
		out[2][0] = in[2][0];
		out[2][1] = in[2][1];
		out[2][2] = in[2][2];
		out[2][3] = in[2][3];
		out[3][0] = in[3][0];
		out[3][1] = in[3][1];
		out[3][2] = in[3][2];
		out[3][3] = in[3][3];
		return out;
	}
}
namespace IR = Iris;
#endif
