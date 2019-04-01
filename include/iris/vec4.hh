#pragma once

#include <ctgmath>
#include <cstring>

namespace Iris
{
	template<typename T> struct vec2;
	template<typename T> struct vec3;
	template<typename T> struct quat;
	template<typename T> struct mat4x4;
	
	template<typename T> struct vec4
	{
		/// X Y Z W
		T data[4];
		
		/// Get a reference to one of the contained values
		inline T &x() { return this->data[0]; }
		inline T &y() { return this->data[1]; }
		inline T &z() { return this->data[2]; }
		inline T &w() { return this->data[3]; }
		inline T const &x() const { return this->data[0]; }
		inline T const &y() const { return this->data[1]; }
		inline T const &z() const { return this->data[2]; }
		inline T const &w() const { return this->data[3]; }
		inline T &r() { return this->data[0]; }
		inline T &g() { return this->data[1]; }
		inline T &b() { return this->data[2]; }
		inline T &a() { return this->data[3]; }
		inline T const &r() const { return this->data[0]; }
		inline T const &g() const { return this->data[1]; }
		inline T const &b() const { return this->data[2]; }
		inline T const &a() const { return this->data[3]; }
		
		//TODO do it
		/// 4-way Swizzling (sort of), 256 permutations
		
		//TODO finish it
		/// 3-way Swizzling (sort of), 64 permutations 
		inline vec3<T> xyz() { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		
		inline vec3<T> xyz() const { return vec3<T>{this->data[0], this->data[1], this->data[2]}; }
		
		/// 2-way Swizzling (sort of), 16 permutations
		inline vec2<T> xx() { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> yy() { return vec2<T>{this->data[1], this->data[1]}; }
		inline vec2<T> zz() { return vec2<T>{this->data[2], this->data[2]}; }
		inline vec2<T> ww() { return vec2<T>{this->data[3], this->data[3]}; }
		inline vec2<T> xy() { return vec2<T>{this->data[0], this->data[1]}; }
		inline vec2<T> xz() { return vec2<T>{this->data[0], this->data[2]}; }
		inline vec2<T> xw() { return vec2<T>{this->data[0], this->data[3]}; }
		inline vec2<T> yx() { return vec2<T>{this->data[1], this->data[0]}; }
		inline vec2<T> yz() { return vec2<T>{this->data[1], this->data[2]}; }
		inline vec2<T> yw() { return vec2<T>{this->data[1], this->data[3]}; }
		inline vec2<T> zx() { return vec2<T>{this->data[2], this->data[0]}; }
		inline vec2<T> zy() { return vec2<T>{this->data[2], this->data[1]}; }
		inline vec2<T> zw() { return vec2<T>{this->data[2], this->data[3]}; }
		inline vec2<T> wx() { return vec2<T>{this->data[3], this->data[0]}; }
		inline vec2<T> wy() { return vec2<T>{this->data[3], this->data[1]}; }
		inline vec2<T> wz() { return vec2<T>{this->data[3], this->data[2]}; }
		inline vec2<T> xx() const { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> yy() const { return vec2<T>{this->data[1], this->data[1]}; }
		inline vec2<T> zz() const { return vec2<T>{this->data[2], this->data[2]}; }
		inline vec2<T> ww() const { return vec2<T>{this->data[3], this->data[3]}; }
		inline vec2<T> xy() const { return vec2<T>{this->data[0], this->data[1]}; }
		inline vec2<T> xz() const { return vec2<T>{this->data[0], this->data[2]}; }
		inline vec2<T> xw() const { return vec2<T>{this->data[0], this->data[3]}; }
		inline vec2<T> yx() const { return vec2<T>{this->data[1], this->data[0]}; }
		inline vec2<T> yz() const { return vec2<T>{this->data[1], this->data[2]}; }
		inline vec2<T> yw() const { return vec2<T>{this->data[1], this->data[3]}; }
		inline vec2<T> zx() const { return vec2<T>{this->data[2], this->data[0]}; }
		inline vec2<T> zy() const { return vec2<T>{this->data[2], this->data[1]}; }
		inline vec2<T> zw() const { return vec2<T>{this->data[2], this->data[3]}; }
		inline vec2<T> wx() const { return vec2<T>{this->data[3], this->data[0]}; }
		inline vec2<T> wy() const { return vec2<T>{this->data[3], this->data[1]}; }
		inline vec2<T> wz() const { return vec2<T>{this->data[3], this->data[2]}; }
		
		inline constexpr vec4<T>() = default;
		
		template<typename U> constexpr vec4<T>(vec4<U> const &other)
		{
			this->data[0] = other.data[0];
			this->data[1] = other.data[1];
			this->data[2] = other.data[2];
			this->data[3] = other.data[3];
		}
		
		/// Construct a v4 out of 4 values
		constexpr inline vec4<T>(T x, T y, T z, T w)
		{
			this->data[0] = x;
			this->data[1] = y;
			this->data[2] = z;
			this->data[3] = w;
		}
		
		constexpr inline vec4<T>(T const &scalar)
		{
			this->data[0] = scalar;
			this->data[1] = scalar;
			this->data[2] = scalar;
			this->data[3] = scalar;
		}
		
		constexpr inline vec4<T>(vec2<T> const &first, vec2<T> const &second)
		{
			this->data[0] = first.x();
			this->data[1] = first.y();
			this->data[2] = second.x();
			this->data[3] = second.y();
		}
		
		constexpr inline vec4<T>(vec2<T> const &first, T const &second, T const &third)
		{
			this->data[0] = first.x();
			this->data[1] = first.y();
			this->data[2] = second;
			this->data[3] = third;
		}
		
		constexpr inline vec4<T>(vec3<T> const &first, T const &second)
		{
			this->data[0] = first.x();
			this->data[1] = first.y();
			this->data[2] = first.z();
			this->data[3] = second;
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
		
		/// Compare equality with another v4
		inline bool operator==(vec4<T> const &other) const
		{
			return this->data[0] == other[0] && this->data[1] == other[1] && this->data[2] == other[2] && this->data[3] == other[3];
		}
		
		/// Compare inequality with another v4
		inline bool operator!=(vec4<T> const &other) const
		{
			return this->data[0] != other[0] || this->data[1] != other[1] || this->data[2] != other[2] || this->data[3] != other[3];
		}
		
		/// Add this v4 to another
		inline vec4<T> operator+(vec4<T> const &other) const
		{
			return vec4<T>{this->data[0] + other[0], this->data[1] + other[1], this->data[2] + other[2], this->data[3] + other[3]};
		}
		
		/// Add a scalar number to this v4
		inline vec4<T> operator+(T const &scalar) const
		{
			return vec4<T>{static_cast<T>(this->data[0] + scalar), static_cast<T>(this->data[1] + scalar), static_cast<T>(this->data[2] + scalar), static_cast<T>(this->data[3] + scalar)};
		}
		
		/// Subtract this v4 from another
		inline vec4<T> operator-(vec4<T> const &other) const
		{
			return vec4<T>{this->data[0] - other[0], this->data[1] - other[1], this->data[2] - other[2], this->data[3] - other[3]};
		}
		
		/// Subtract a scalar number from this v4
		inline vec4<T> operator-(T const &scalar) const
		{
			return vec4<T>{static_cast<T>(this->data[0] - scalar), static_cast<T>(this->data[1] - scalar), static_cast<T>(this->data[2] - scalar), static_cast<T>(this->data[3] - scalar)};
		}
		
		/// Negate this v4
		inline vec4<T> operator-() const
		{
			return vec4<T>{-this->data[0], -this->data[1], -this->data[2], -this->data[3]};
		}
		
		/// Multiply this v4 with another
		inline vec4<T> operator*(vec4<T> const &other) const
		{
			return vec4<T>{this->data[0] * other[0], this->data[1] * other[1], this->data[2] * other[2], this->data[3] * other[3]};
		}
		
		/// Multiply this v4 by a scalar number
		inline vec4<T> operator*(T scalar) const
		{
			return vec4<T>{static_cast<T>(this->data[0] * scalar), static_cast<T>(this->data[1] * scalar), static_cast<T>(this->data[2] * scalar), static_cast<T>(this->data[3] * scalar)};
		}
		
		inline vec4<T> operator*(mat4x4<T> const &mat)
		{
			return vec4<T>{
					this->data[0] * mat[0][0] + this->data[1] * mat[0][1] + this->data[2] * mat[0][2] + this->data[3] * mat[0][3],
					this->data[0] * mat[1][0] + this->data[1] * mat[1][1] + this->data[2] * mat[1][2] + this->data[3] * mat[1][3],
					this->data[0] * mat[2][0] + this->data[1] * mat[2][1] + this->data[2] * mat[2][2] + this->data[3] * mat[2][3],
					this->data[0] * mat[3][0] + this->data[1] * mat[3][1] + this->data[2] * mat[3][2] + this->data[3] * mat[3][3],
			};
		}
		
		/// Divide this v4 by another
		inline vec4<T> operator/(vec4<T> const &other) const
		{
			return vec4<T>{this->data[0] / other[0], this->data[1] / other[1], this->data[2] / other[2], this->data[3] / other[3]};
		}
		
		/// Divide this v4 by a scalar number
		inline vec4<T> operator/(T const &scalar) const
		{
			return vec4<T>{static_cast<T>(this->data[0] / scalar), static_cast<T>(this->data[1] / scalar), static_cast<T>(this->data[2] / scalar), static_cast<T>(this->data[3] / scalar)};
		}
		
		/// Compound add this v4 to another
		inline vec4<T> operator+=(vec4<T> const &other)
		{
			this->data[0] += other[0];
			this->data[1] += other[1];
			this->data[2] += other[2];
			this->data[3] += other[3];
			return *this;
		}
		
		/// Compound subtract this v4 from another
		inline vec4<T> operator-=(vec4<T> const &other)
		{
			this->data[0] -= other[0];
			this->data[1] -= other[1];
			this->data[2] -= other[2];
			this->data[3] -= other[3];
			return *this;
		}
		
		/// Compound multiply this v4 with another
		inline vec4<T> operator*=(vec4<T> const &other)
		{
			this->data[0] *= other[0];
			this->data[1] *= other[1];
			this->data[2] *= other[2];
			this->data[3] *= other[3];
			return *this;
		}
		
		/// Compound divide this v4 by another
		inline vec4<T> operator/=(vec4<T> const &other)
		{
			this->data[0] /= other[0];
			this->data[1] /= other[1];
			this->data[2] /= other[2];
			this->data[3] /= other[3];
			return *this;
		}
		
		/// Increment all values in this v4 (prefix)
		inline vec4<T> &operator++()
		{
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			this->data[3]++;
			return *this;
		}
		
		/// Increment all values in this v4 (postfix)
		inline vec4<T> &operator++(int)
		{
			vec4<T> out = *this;
			this->data[0]++;
			this->data[1]++;
			this->data[2]++;
			this->data[3]++;
			return out;
		}
		
		/// Decrement all values in this v4 (prefix)
		inline vec4<T> &operator--()
		{
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			this->data[3]--;
			return *this;
		}
		
		/// Decrement all values in this v4 (postfix)
		inline vec4<T> &operator--(int)
		{
			vec4<T> out = *this;
			this->data[0]--;
			this->data[1]--;
			this->data[2]--;
			this->data[3]--;
			return out;
		}
		
		/// Set all values individually
		inline void set(T x, T y, T z, T w)
		{
			this->data[0] = x;
			this->data[1] = y;
			this->data[2] = z;
			this->data[3] = w;
		}
		
		/// Set all values to one given value
		inline void setAll(T value)
		{
			this->set(value, value, value, value);
		}
		
		/// Invert sign on all values
		inline void invert()
		{
			this->data[0] = -this->data[0];
			this->data[1] = -this->data[1];
			this->data[2] = -this->data[2];
			this->data[3] = -this->data[3];
		}
		
		/// Get an inverted v4
		inline vec4<T> inverse() const
		{
			return vec4<T>{-this->data[0], -this->data[1], -this->data[2], -this->data[3]};
		}
		
		/// Get the magnitude of this v4
		inline T mag() const
		{
			return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2] + this->data[3] * this->data[3]);
		}
		
		/// Get the dot product of this v4 and another
		inline T dot(vec4<T> const &b) const
		{
			return this->data[3] * b.w + this->data[0] * b.x + this->data[1] * b.y + this->data[2] * b.z;
		}
		
		/// Normalize this v4
		inline void normalize()
		{
			T length = this->mag();
			this->data[3] /= length;
			this->data[0] /= length;
			this->data[1] /= length;
			this->data[2] /= length;
		}
		
		/// Get a normalized v4
		inline vec4<T> normalized() const
		{
			vec4<T> out;
			T length = this->mag();
			out[0] = this->data[0] / length;
			out[1] = this->data[1] / length;
			out[2] = this->data[2] / length;
			out[3] = this->data[3] / length;
			return out;
		}
		
		using value_type = T;
		
		inline size_t size() const
		{
			return 4;
		}
		
		/// Compose a string out of this v4's values
		inline std::string toString() const
		{
			std::string out = "(vec4)\n[x: ";
			out += std::to_string(this->data[0]);
			out += " y: ";
			out += std::to_string(this->data[1]);
			out += " z: ";
			out += std::to_string(this->data[2]);
			out += " w: ";
			out += std::to_string(this->data[3]);
			out += "]\n";
			return out;
		}
		
		/// Print this v4 with printf
		inline void print(std::string const &name) const
		{
			printf("%s: %s\n", name.data(), this->toString().data());
		}
	};
	static_assert(std::is_pod<vec4<int32_t>>());
}
namespace IR = Iris;
