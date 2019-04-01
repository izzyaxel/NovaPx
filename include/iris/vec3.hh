#pragma once

#include "vec2.hh"

namespace Iris
{
	template<typename T> struct vec4;
	template<typename T> struct quat;
	
	template<typename T> struct vec3
	{
		/// X Y Z
		T data[3];
		
		/// Get a reference to one of the contained values
		inline T &x() { return this->data[0]; }
		inline T &y() { return this->data[1]; }
		inline T &z() { return this->data[2]; }
		inline T const &x() const { return this->data[0]; }
		inline T const &y() const { return this->data[1]; }
		inline T const &z() const { return this->data[2]; }
		
		inline T &r() { return this->data[0]; }
		inline T &g() { return this->data[1]; }
		inline T &b() { return this->data[2]; }
		inline T const &r() const { return this->data[0]; }
		inline T const &g() const { return this->data[1]; }
		inline T const &b() const { return this->data[2]; }
		
		// 3-way Swizzling (sort of), 26 permutations (excluded xyz)
		inline vec3<T> xxx() { return vec3<T>{this->data[0]}; }
		inline vec3<T> yyy() { return vec3<T>{this->data[1]}; }
		inline vec3<T> zzz() { return vec3<T>{this->data[2]}; }
		inline vec3<T> zyx() { return vec3<T>{this->data[2], this->data[1], this->data[0]}; }
		inline vec3<T> xxy() { return vec3<T>{this->data[0], this->data[0], this->data[1]}; }
		inline vec3<T> xxz() { return vec3<T>{this->data[0], this->data[0], this->data[2]}; }
		inline vec3<T> yyx() { return vec3<T>{this->data[1], this->data[1], this->data[0]}; }
		inline vec3<T> yyz() { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		inline vec3<T> zzx() { return vec3<T>{this->data[2], this->data[2], this->data[0]}; }
		inline vec3<T> zzy() { return vec3<T>{this->data[2], this->data[2], this->data[1]}; }
		inline vec3<T> xyy() { return vec3<T>{this->data[0], this->data[1], this->data[1]}; }
		inline vec3<T> xzz() { return vec3<T>{this->data[0], this->data[2], this->data[2]}; }
		inline vec3<T> yxx() { return vec3<T>{this->data[1], this->data[0], this->data[0]}; }
		inline vec3<T> yzz() { return vec3<T>{this->data[1], this->data[2], this->data[2]}; }
		inline vec3<T> zxx() { return vec3<T>{this->data[2], this->data[0], this->data[0]}; }
		inline vec3<T> zyy() { return vec3<T>{this->data[2], this->data[1], this->data[1]}; }
		inline vec3<T> xyx() { return vec3<T>{this->data[0], this->data[1], this->data[0]}; }
		inline vec3<T> xzx() { return vec3<T>{this->data[0], this->data[2], this->data[0]}; }
		inline vec3<T> yxy() { return vec3<T>{this->data[1], this->data[0], this->data[1]}; }
		inline vec3<T> yzy() { return vec3<T>{this->data[1], this->data[2], this->data[1]}; }
		inline vec3<T> zxz() { return vec3<T>{this->data[2], this->data[0], this->data[2]}; }
		inline vec3<T> zyz() { return vec3<T>{this->data[2], this->data[1], this->data[2]}; }
		inline vec3<T> xzy() { return vec3<T>{this->data[0], this->data[2], this->data[1]}; }
		inline vec3<T> yzx() { return vec3<T>{this->data[1], this->data[2], this->data[0]}; }
		inline vec3<T> zxy() { return vec3<T>{this->data[2], this->data[0], this->data[1]}; }
		inline vec3<T> yxz() { return vec3<T>{this->data[1], this->data[0], this->data[2]}; }
		inline vec3<T> xxx() const { return vec3<T>{this->data[0]}; }
		inline vec3<T> yyy() const { return vec3<T>{this->data[1]}; }
		inline vec3<T> zzz() const { return vec3<T>{this->data[2]}; }
		inline vec3<T> zyx() const { return vec3<T>{this->data[2], this->data[1], this->data[0]}; }
		inline vec3<T> xxy() const { return vec3<T>{this->data[0], this->data[0], this->data[1]}; }
		inline vec3<T> xxz() const { return vec3<T>{this->data[0], this->data[0], this->data[2]}; }
		inline vec3<T> yyx() const { return vec3<T>{this->data[1], this->data[1], this->data[0]}; }
		inline vec3<T> yyz() const { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		inline vec3<T> zzx() const { return vec3<T>{this->data[2], this->data[2], this->data[0]}; }
		inline vec3<T> zzy() const { return vec3<T>{this->data[2], this->data[2], this->data[1]}; }
		inline vec3<T> xyy() const { return vec3<T>{this->data[0], this->data[1], this->data[1]}; }
		inline vec3<T> xzz() const { return vec3<T>{this->data[0], this->data[2], this->data[2]}; }
		inline vec3<T> yxx() const { return vec3<T>{this->data[1], this->data[0], this->data[0]}; }
		inline vec3<T> yzz() const { return vec3<T>{this->data[1], this->data[2], this->data[2]}; }
		inline vec3<T> zxx() const { return vec3<T>{this->data[2], this->data[0], this->data[0]}; }
		inline vec3<T> zyy() const { return vec3<T>{this->data[2], this->data[1], this->data[1]}; }
		inline vec3<T> xyx() const { return vec3<T>{this->data[0], this->data[1], this->data[0]}; }
		inline vec3<T> xzx() const { return vec3<T>{this->data[0], this->data[2], this->data[0]}; }
		inline vec3<T> yxy() const { return vec3<T>{this->data[1], this->data[0], this->data[1]}; }
		inline vec3<T> yzy() const { return vec3<T>{this->data[1], this->data[2], this->data[1]}; }
		inline vec3<T> zxz() const { return vec3<T>{this->data[2], this->data[0], this->data[2]}; }
		inline vec3<T> zyz() const { return vec3<T>{this->data[2], this->data[1], this->data[2]}; }
		inline vec3<T> xzy() const { return vec3<T>{this->data[0], this->data[2], this->data[1]}; }
		inline vec3<T> yzx() const { return vec3<T>{this->data[1], this->data[2], this->data[0]}; }
		inline vec3<T> zxy() const { return vec3<T>{this->data[2], this->data[0], this->data[1]}; }
		inline vec3<T> yxz() const { return vec3<T>{this->data[1], this->data[0], this->data[2]}; }
		
		inline vec3<T> rrr() { return vec3<T>{this->data[0]}; }
		inline vec3<T> ggg() { return vec3<T>{this->data[1]}; }
		inline vec3<T> bbb() { return vec3<T>{this->data[2]}; }
		inline vec3<T> bgr() { return vec3<T>{this->data[2], this->data[1], this->data[0]}; }
		inline vec3<T> rrg() { return vec3<T>{this->data[0], this->data[0], this->data[1]}; }
		inline vec3<T> rrb() { return vec3<T>{this->data[0], this->data[0], this->data[2]}; }
		inline vec3<T> ggr() { return vec3<T>{this->data[1], this->data[1], this->data[0]}; }
		inline vec3<T> ggb() { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		inline vec3<T> bbr() { return vec3<T>{this->data[2], this->data[2], this->data[0]}; }
		inline vec3<T> bbg() { return vec3<T>{this->data[2], this->data[2], this->data[1]}; }
		inline vec3<T> rgg() { return vec3<T>{this->data[0], this->data[1], this->data[1]}; }
		inline vec3<T> rbb() { return vec3<T>{this->data[0], this->data[2], this->data[2]}; }
		inline vec3<T> grr() { return vec3<T>{this->data[1], this->data[0], this->data[0]}; }
		inline vec3<T> gbb() { return vec3<T>{this->data[1], this->data[2], this->data[2]}; }
		inline vec3<T> brr() { return vec3<T>{this->data[2], this->data[0], this->data[0]}; }
		inline vec3<T> bgg() { return vec3<T>{this->data[2], this->data[1], this->data[1]}; }
		inline vec3<T> rgr() { return vec3<T>{this->data[0], this->data[1], this->data[0]}; }
		inline vec3<T> rbr() { return vec3<T>{this->data[0], this->data[2], this->data[0]}; }
		inline vec3<T> grg() { return vec3<T>{this->data[1], this->data[0], this->data[1]}; }
		inline vec3<T> gbg() { return vec3<T>{this->data[1], this->data[2], this->data[1]}; }
		inline vec3<T> brb() { return vec3<T>{this->data[2], this->data[0], this->data[2]}; }
		inline vec3<T> bgb() { return vec3<T>{this->data[2], this->data[1], this->data[2]}; }
		inline vec3<T> rbg() { return vec3<T>{this->data[0], this->data[2], this->data[1]}; }
		inline vec3<T> gbr() { return vec3<T>{this->data[1], this->data[2], this->data[0]}; }
		inline vec3<T> brg() { return vec3<T>{this->data[2], this->data[0], this->data[1]}; }
		inline vec3<T> grb() { return vec3<T>{this->data[1], this->data[0], this->data[2]}; }
		inline vec3<T> rrr() const { return vec3<T>{this->data[0]}; }
		inline vec3<T> ggg() const { return vec3<T>{this->data[1]}; }
		inline vec3<T> bbb() const { return vec3<T>{this->data[2]}; }
		inline vec3<T> bgr() const { return vec3<T>{this->data[2], this->data[1], this->data[0]}; }
		inline vec3<T> rrg() const { return vec3<T>{this->data[0], this->data[0], this->data[1]}; }
		inline vec3<T> rrb() const { return vec3<T>{this->data[0], this->data[0], this->data[2]}; }
		inline vec3<T> ggr() const { return vec3<T>{this->data[1], this->data[1], this->data[0]}; }
		inline vec3<T> ggb() const { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		inline vec3<T> bbr() const { return vec3<T>{this->data[2], this->data[2], this->data[0]}; }
		inline vec3<T> bbg() const { return vec3<T>{this->data[2], this->data[2], this->data[1]}; }
		inline vec3<T> rgg() const { return vec3<T>{this->data[0], this->data[1], this->data[1]}; }
		inline vec3<T> rbb() const { return vec3<T>{this->data[0], this->data[2], this->data[2]}; }
		inline vec3<T> grr() const { return vec3<T>{this->data[1], this->data[0], this->data[0]}; }
		inline vec3<T> gbb() const { return vec3<T>{this->data[1], this->data[2], this->data[2]}; }
		inline vec3<T> brr() const { return vec3<T>{this->data[2], this->data[0], this->data[0]}; }
		inline vec3<T> bgg() const { return vec3<T>{this->data[2], this->data[1], this->data[1]}; }
		inline vec3<T> rgr() const { return vec3<T>{this->data[0], this->data[1], this->data[0]}; }
		inline vec3<T> rbr() const { return vec3<T>{this->data[0], this->data[2], this->data[0]}; }
		inline vec3<T> grg() const { return vec3<T>{this->data[1], this->data[0], this->data[1]}; }
		inline vec3<T> gbg() const { return vec3<T>{this->data[1], this->data[2], this->data[1]}; }
		inline vec3<T> brb() const { return vec3<T>{this->data[2], this->data[0], this->data[2]}; }
		inline vec3<T> bgb() const { return vec3<T>{this->data[2], this->data[1], this->data[2]}; }
		inline vec3<T> rbg() const { return vec3<T>{this->data[0], this->data[2], this->data[1]}; }
		inline vec3<T> gbr() const { return vec3<T>{this->data[1], this->data[2], this->data[0]}; }
		inline vec3<T> brg() const { return vec3<T>{this->data[2], this->data[0], this->data[1]}; }
		inline vec3<T> grb() const { return vec3<T>{this->data[1], this->data[0], this->data[2]}; }
		
		// 2-way Swizzling (sort of), 9 permutations
		inline vec2<T> xx() { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> xy() { return vec2<T>{this->data[0], this->data[1]}; }
		inline vec2<T> xz() { return vec2<T>{this->data[0], this->data[2]}; }
		inline vec2<T> yy() { return vec2<T>{this->data[1], this->data[1]}; }
		inline vec2<T> yx() { return vec2<T>{this->data[1], this->data[0]}; }
		inline vec2<T> yz() { return vec2<T>{this->data[1], this->data[2]}; }
		inline vec2<T> zz() { return vec2<T>{this->data[2], this->data[2]}; }
		inline vec2<T> zx() { return vec2<T>{this->data[2], this->data[0]}; }
		inline vec2<T> zy() { return vec2<T>{this->data[2], this->data[1]}; }
		inline vec2<T> xx() const { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> xy() const { return vec2<T>{this->data[0], this->data[1]}; }
		inline vec2<T> xz() const { return vec2<T>{this->data[0], this->data[2]}; }
		inline vec2<T> yy() const { return vec2<T>{this->data[1], this->data[1]}; }
		inline vec2<T> yx() const { return vec2<T>{this->data[1], this->data[0]}; }
		inline vec2<T> yz() const { return vec2<T>{this->data[1], this->data[2]}; }
		inline vec2<T> zz() const { return vec2<T>{this->data[2], this->data[2]}; }
		inline vec2<T> zx() const { return vec2<T>{this->data[2], this->data[0]}; }
		inline vec2<T> zy() const { return vec2<T>{this->data[2], this->data[1]}; }
		
		inline constexpr vec3<T>() = default;
		
		template<typename U> constexpr vec3<T>(vec3<U> const &other)
		{
			this->data[0] = other.data[0];
			this->data[1] = other.data[1];
			this->data[2] = other.data[2];
		}
		
		/// Construct a v3 out of 3 values
		constexpr inline vec3<T>(T const &x, T const &y, T const &z)
		{
			this->data[0] = x;
			this->data[1] = y;
			this->data[2] = z;
		}
		
		constexpr inline vec3<T>(T const &scalar)
		{
			this->data[0] = scalar;
			this->data[1] = scalar;
			this->data[2] = scalar;
		}
		
		constexpr inline vec3<T>(vec2<T> const &first, T const &second)
		{
			this->data[0] = first.x();
			this->data[1] = first.y();
			this->data[2] = second;
		}
		
		/// Truncate a v4 to a v3
		constexpr inline vec3<T>(vec4<T> const &trunc)
		{
			this->data[0] = trunc.x();
			this->data[1] = trunc.y();
			this->data[2] = trunc.z();
		}
		
		/// Subscript operator
		inline T &operator[](size_t index)
		{
			return this->data[index];
		}
		
		inline T const &operator[](size_t index) const
		{
			return this->data[index];
		}
		
		/// Compare equality with another v3
		inline bool operator==(vec3<T> const &other) const
		{
			return this->data[0] == other[0] && this->data[1] == other[1] && this->data[2] == other[2];
		}
		
		/// Compare inequality with another v3
		inline bool operator!=(vec3<T> const &other) const
		{
			return this->data[0] != other[0] || this->data[1] != other[1] || this->data[2] != other[2];
		}
		
		/// Add this v3 to another
		inline vec3<T> operator+(vec3<T> const &other) const
		{
			return vec3<T>{this->data[0] + other[0], this->data[1] + other[1], this->data[2] + other[2]};
		}
		
		/// Add a scalar number to this v3
		inline vec3<T> operator+(T const &scalar) const
		{
			return vec3<T>{static_cast<T>(this->data[0] + scalar), static_cast<T>(this->data[1] + scalar), static_cast<T>(this->data[2] + scalar)};
		}
		
		/// Subtract this v3 from another
		inline vec3<T> operator-(vec3<T> const &other) const
		{
			return vec3<T>{this->data[0] - other[0], this->data[1] - other[1], this->data[2] - other[2]};
		}
		
		/// Subtract a scalar number from this v3
		inline vec3<T> operator-(T const &scalar) const
		{
			return vec3<T>{static_cast<T>(this->data[0] - scalar), static_cast<T>(this->data[1] - scalar), static_cast<T>(this->data[2] - scalar)};
		}
		
		/// Negate this v3
		inline vec3<T> operator-() const
		{
			return vec3<T>{-this->data[0], -this->data[1], -this->data[2]};
		}
		
		/// Multiply this v3 with another
		inline vec3<T> operator*(vec3<T> const &other) const
		{
			return vec3<T>{this->data[0] * other[0], this->data[1] * other[1], this->data[2] * other[2]};
		}
		
		/// Multiply this v3 by a scalar number
		inline vec3<T> operator*(T scalar) const
		{
			return vec3<T>{static_cast<T>(this->data[0] * scalar), static_cast<T>(this->data[1] * scalar), static_cast<T>(this->data[2] * scalar)};
		}
		
		inline vec3<T> operator*(quat<T> const &in)
		{
			vec3<T> q{in[0], in[1], in[2]};
			vec3<T> w1 = this->cross(q) * static_cast<T>(2);
			return *this + w1 * in[3] + w1.cross(q);
		}
		
		/// Divide this v3 by another
		inline vec3<T> operator/(vec3<T> const &other) const
		{
			return vec3<T>{this->data[0] / other[0], this->data[1] / other[1], this->data[2] / other[2]};
		}
		
		/// Divide this v3 by a scalar number
		inline vec3<T> operator/(T const &scalar) const
		{
			return vec3<T>{static_cast<T>(this->data[0] / scalar), static_cast<T>(this->data[1] / scalar), static_cast<T>(this->data[2] / scalar)};
		}
		
		/// Compound add this v3 to another
		inline vec3<T> operator+=(vec3<T> const &other)
		{
			this->data[0] += other[0];
			this->data[1] += other[1];
			this->data[2] += other[2];
			return *this;
		}
		
		/// Compound subtract this v3 from another
		inline vec3<T> operator-=(vec3<T> const &other)
		{
			this->data[0] -= other[0];
			this->data[1] -= other[1];
			this->data[2] -= other[2];
			return *this;
		}
		
		/// Compound multiply this v3 with another
		inline vec3<T> operator*=(vec3<T> const &other)
		{
			this->data[0] *= other[0];
			this->data[1] *= other[1];
			this->data[2] *= other[2];
			return *this;
		}
		
		/// Compound divide this v3 by another
		inline vec3<T> operator/=(vec3<T> const &other)
		{
			this->data[0] /= other[0];
			this->data[1] /= other[1];
			this->data[2] /= other[2];
			return *this;
		}
		
		/// Increment all values in this v3 (prefix)
		inline vec3<T> &operator++()
		{
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			return *this;
		}
		
		/// Increment all values in this v3 (postfix)
		inline vec3<T> &operator++(int)
		{
			vec3<T> out = *this;
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			return out;
		}
		
		/// Decrement all values in this v3 (prefix)
		inline vec3<T> &operator--()
		{
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			return *this;
		}
		
		/// Decrement all values in this v3 (postfix)
		inline vec3<T> &operator--(int)
		{
			vec3<T> out = *this;
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			return out;
		}
		
		/// Set all values individually
		inline void set(T const &x, T const &y, T const &z)
		{
			this->data[0] = x;
			this->data[1] = y;
			this->data[2] = z;
		}
		
		/// Set all values to one given value
		inline void setAll(T const &value)
		{
			this->set(value, value, value);
		}
		
		/// Invert sign on all values
		inline void invert()
		{
			this->data[0] = -this->data[0];
			this->data[1] = -this->data[1];
			this->data[2] = -this->data[2];
		}
		
		/// Get an inverted v3
		inline vec3<T> inverse() const
		{
			return vec3<T>{-this->data[0], -this->data[1], -this->data[2]};
		}
		
		/// Get the magnitude of this v3
		inline T mag() const
		{
			return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2]);
		}
		
		/// Get the dot product of this v3 and another
		inline T dot(vec3<T> const &b) const
		{ return this->data[0] * b[0] + this->data[1] * b[1] + this->data[2] * b[2]; }
		
		/// Get the cross product of this v3 and another
		inline vec3<T> cross(vec3<T> const &b) const
		{
			vec3<T> out;
			out[0] = this->data[1] * b[2] - this->data[2] * b[1];
			out[1] = this->data[2] * b[0] - this->data[0] * b[2];
			out[2] = this->data[0] * b[1] - this->data[1] * b[0];
			return out;
		}
		
		///Normalize this v3
		inline void normalize()
		{
			T length = this->mag();
			this->data[0] /= length;
			this->data[1] /= length;
			this->data[2] /= length;
		}
		
		/// Get a normalized v3
		inline vec3<T> normalized() const
		{
			vec3<T> out;
			T length = this->mag();
			out[0] = this->data[0] / length;
			out[1] = this->data[1] / length;
			out[2] = this->data[2] / length;
			return out;
		}
		
		/// Create a yaw/pitch/roll rotation from relative mouse movement values
		inline static vec3<T> rotateFromMouseEuler(T xrel, T yrel, T lookSensitivity)
		{
			vec3<T> out{};
			out[0] = -yrel * lookSensitivity;
			out[1] = -xrel * lookSensitivity;
			out[2] = 0;
			return out;
		}
		
		/// (For directional unit vectors) Check if the direction this v3 indicates is cardinal
		inline bool isCardinal() const
		{
			return std::abs(this->data[0]) + std::abs(this->data[1]) + std::abs(this->data[2]) == 1;
		}
		
		using value_type = T;
		
		inline size_t size() const
		{
			return 3;
		}
		
		/// Compose a string out of this v3's values
		inline std::string toString() const
		{
			std::string out = "(vec3)\n[x: ";
			out += std::to_string(this->data[0]);
			out += " y: ";
			out += std::to_string(this->data[1]);
			out += " z: ";
			out += std::to_string(this->data[2]);
			out += "]\n";
			return out;
		}
		
		/// Print this v3 with printf
		inline void print(std::string const &name) const
		{
			printf("%s: %s\n", name.data(), this->toString().data());
		}
	};
	static_assert(std::is_pod<vec3<int32_t>>());
}
namespace IR = Iris;
