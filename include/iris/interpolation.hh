#pragma once

#include "vec2.hh"
#include "vec3.hh"
#include "general.hh"

namespace Iris
{
	/// Lerp between 2 2-dimensional vectors
	template<typename T> vec2<T> lerpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		vec2<T> out;
		out[0] = progress * dest[0] + (1 - progress) * src[0];
		out[1] = progress * dest[1] + (1 - progress) * src[1];
		return out;
	}

	/// Ease out lerp: fast in slow out
	template<typename T> vec2<T> eoerpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>(std::sin(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Ease in lerp: slow in fast out
	template<typename T> vec2<T> eierpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease out lerp: fast in slower out
	template<typename T> vec2<T> exeoerpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>(std::sin((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease in lerp: slower in fast out
	template<typename T> vec2<T> exeierpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Smoothstep lerp: slow in slow out
	template<typename T> vec2<T> serpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>((progress * progress) * (static_cast<T>(3.0) - (static_cast<T>(2.0) * progress))));
	}

	/// Smootherstep lerp: slower in slower out
	template<typename T> vec2<T> sserpV2(vec2<T> const &src, vec2<T> const &dest, float progress)
	{
		return lerpV2(src, dest, static_cast<float>(std::pow(progress, 3) * (progress * (static_cast<T>(6.0) * progress - static_cast<T>(15.0)) + static_cast<T>(10.0))));
	}

	/// Lerp between 2 3-dimensional vectors
	template<typename T> vec3<T> lerpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		vec3<T> out;
		out[0] = progress * dest[0] + (static_cast<T>(1.0) - progress) * src[0];
		out[1] = progress * dest[1] + (static_cast<T>(1.0) - progress) * src[1];
		out[2] = progress * dest[2] + (static_cast<T>(1.0) - progress) * src[2];
		return out;
	}

	/// Ease out lerp: fast in slow out
	template<typename T> vec3<T> eoerpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>(std::sin(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Ease in lerp: slow in fast out
	template<typename T> vec3<T> eierpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease out lerp: fast in slower out
	template<typename T> vec3<T> exeoerpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>(std::sin((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease in lerp slower in fast out
	template<typename T> vec3<T> exeierpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Smoothstep lerp: slow in slow out
	template<typename T> vec3<T> serpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>((progress * progress) * (static_cast<T>(3.0) - (static_cast<T>(2.0) * progress))));
	}

	/// Smootherstep lerp: slower in slower out
	template<typename T> vec3<T> sserpV3(vec3<T> const &src, vec3<T> const &dest, float progress)
	{
		return lerpV3(src, dest, static_cast<float>(std::pow(progress, 3) * (progress * (static_cast<T>(6.0) * progress - static_cast<T>(15.0)) + static_cast<T>(10.0))));
	}

	/// Lerp between 2 4-dimensional vectors
	template<typename T> vec4<T> lerpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		vec4<T> out;
		out[0] = progress * dest[0] + (1 - progress) * src[0];
		out[1] = progress * dest[1] + (1 - progress) * src[1];
		out[2] = progress * dest[2] + (1 - progress) * src[2];
		out[3] = progress * dest[3] + (1 - progress) * src[3];
		return out;
	}

	/// Ease out lerp: fast in slow out
	template<typename T> vec4<T> eoerpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>(std::sin(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Ease in lerp: slow in fast out
	template<typename T> vec4<T> eierpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos(progress * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease out lerp: fast in slower out
	template<typename T> vec4<T> exeoerpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>(std::sin((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Exponential ease in lerp: slower in fast out
	template<typename T> vec4<T> exeierpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>(static_cast<T>(1.0) - std::cos((progress * progress) * pi<T> * static_cast<T>(0.5))));
	}

	/// Smoothstep lerp: slow in slow out
	template<typename T> vec4<T> serpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>((progress * progress) * (static_cast<T>(3.0) - (static_cast<T>(2.0) * progress))));
	}

	/// Smootherstep lerp: slower in slower out
	template<typename T> vec4<T> sserpV4(vec4<T> const &src, vec4<T> const &dest, float progress)
	{
		return lerpV4(src, dest, static_cast<float>(std::pow(progress, 3) * (progress * (static_cast<T>(6.0) * progress - static_cast<T>(15.0)) + static_cast<T>(10.0))));
	}

	/// Quaternion spherical linear interpolation
	template<typename T> quat<T> slerpQuat(quat<T> const &A, quat<T> const &B, T value)
	{
		T dot = A[0] * B[0] + A[1] * B[1] + A[2] * B[2] + A[3] * B[3];
		if (dot > 1) dot = 1;
		if (dot < -1) dot = -1;
		if (dot == 1) return A;
		T angle = std::acos(dot);
		T sqi = std::sqrt(static_cast<T>(1) - dot * dot);
		T vA = std::sin((static_cast<T>(1) - value) * angle) / sqi;
		T vB = std::sin(value * angle) / sqi;
		return quat<T>{
				A[0] * vA + B[0] * vB,
				A[1] * vA + B[1] * vB,
				A[2] * vA + B[2] * vB,
				A[3] * vA + B[3] * vB}.normalized();
	}
}
namespace IR = Iris;
