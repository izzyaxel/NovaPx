#pragma once

#include "vec3.hh"
#include "mat4.hh"
#include "general.hh"

#include <ctgmath>
#include <vector>

namespace Iris
{
	/// Check if the given vertex is within the camera's frustum
	/// \param mvp The completed model view projection matrix of the camera you want to check visibility with
	template<typename T> bool isVertexOnscreen(mat4x4<T> const &mvp, vec3<T> const &vertex)
	{
		vec3<T> result = vec3<T>{vec4<T>{vertex, static_cast<T>(1)} * mvp};
		return result.x() < static_cast<T>(1) && result.x() > static_cast<T>(-1) &&
		       result.y() < static_cast<T>(1) && result.y() > static_cast<T>(-1) &&
		       result.z() < static_cast<T>(1) && result.z() > static_cast<T>(-1);
	}
	
	/// Translate a mouse coordinate over the openGL window to a ray into 3D space
	template<typename T> vec3<T> mouseToWorld(int32_t clickX, int32_t clickY, mat4x4<T> const &view, mat4x4<T> const &projection, uint32_t width, uint32_t height)
	{
		mat4x4<T> inv = mat4x4<T>(view * projection).inverse();
		double ndcX = (static_cast<double>(clickX) / static_cast<double>(width)) * static_cast<double>(2) - static_cast<double>(1);
		double ndcY = (static_cast<double>(clickY) / static_cast<double>(height)) * static_cast<double>(2) - static_cast<double>(1);
		vec4<T> clip = {static_cast<T>(ndcX), static_cast<T>(ndcY), static_cast<T>(1), static_cast<T>(1)};
		clip = inv * clip;
		clip /= clip[3];
		return vec3<T>{clip};
	}
}
namespace IR = Iris;
