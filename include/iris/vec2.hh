#pragma once

#include <ctgmath>
#include <cstring>

namespace Iris
{
	template<typename T> struct vec2
	{
		T data[2];
		
		inline T &x() { return this->data[0]; }
		inline T &y() { return this->data[1]; }
		inline T const &x() const { return this->data[0]; }
		inline T const &y() const { return this->data[1]; }
		
		// 2-way Swizzling (sort of) 2 permutations
		inline vec2<T> xx() { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> yy() { return vec2<T>{this->data[1], this->data[1]}; }
		inline vec2<T> xx() const { return vec2<T>{this->data[0], this->data[0]}; }
		inline vec2<T> yy() const { return vec2<T>{this->data[1], this->data[1]}; }
		
		inline constexpr vec2<T>() = default;
		
		template<typename U> constexpr vec2<T>(vec2<U> const &other)
		{
			this->data[0] = other.data[0];
			this->data[1] = other.data[1];
		}
		
		constexpr inline vec2<T>(T x, T y)
		{
			this->data[0] = x;
			this->data[1] = y;
		}
		
		constexpr inline vec2<T>(T const &scalar)
		{
			this->data[0] = scalar;
			this->data[1] = scalar;
		}
		
		inline T &operator[](size_t index)
		{
			return this->data[index];
		}
		
		inline T const &operator[](size_t index) const
		{
			return this->data[index];
		}
		
		inline bool operator==(vec2<T> const &other) const
		{
			return this->data[0] == other[0] && this->data[1] == other[1];
		}
		
		inline bool operator!=(vec2<T> const &other) const
		{
			return this->data[0] != other[0] || this->data[1] != other[1];
		}
		
		inline vec2<T> operator+(vec2<T> const &other) const
		{
			return vec2<T>{this->data[0] + other[0], this->data[1] + other[1]};
		}
		
		inline vec2<T> operator+(T const &scalar) const
		{
			return vec2<T>{static_cast<T>(this->data[0] + scalar), static_cast<T>(this->data[1] + scalar)};
		}
		
		inline vec2<T> operator-(vec2<T> const &other) const
		{
			return vec2<T>{this->data[0] - other[0], this->data[1] - other[1]};
		}
		
		inline vec2<T> operator-(T const &scalar) const
		{
			return vec2<T>{static_cast<T>(this->data[0] - scalar), static_cast<T>(this->data[1] - scalar)};
		}
		
		inline vec2<T> operator-() const
		{
			return vec2<T>{-this->data[0], -this->data[1]};
		}
		
		inline vec2<T> operator*(vec2<T> const &other) const
		{
			return vec2<T>{this->data[0] * other[0], this->data[1] * other[1]};
		}
		
		inline vec2<T> operator*(T scalar) const
		{
			return vec2<T>{static_cast<T>(this->data[0] * scalar), static_cast<T>(this->data[1] * scalar)};
		}
		
		inline vec2<T> operator/(vec2<T> const &other) const
		{
			return vec2<T>{this->data[0] / other[0], this->data[1] / other[1]};
		}
		
		inline vec2<T> operator/(T const &scalar) const
		{
			return vec2<T>{static_cast<T>(this->data[0] / scalar), static_cast<T>(this->data[1] / scalar)};
		}
		
		inline vec2<T> &operator+=(vec2<T> const &other)
		{
			this->data[0] += other[0];
			this->data[1] += other[1];
			return *this;
		}
		
		inline vec2<T> &operator-=(vec2<T> const &other)
		{
			this->data[0] -= other[0];
			this->data[1] -= other[1];
			return *this;
		}
		
		inline vec2<T> &operator*=(vec2<T> const &other)
		{
			this->data[0] *= other[0];
			this->data[1] *= other[1];
			return *this;
		}
		
		inline vec2<T> &operator/=(vec2<T> const &other)
		{
			this->data[0] /= other[0];
			this->data[1] /= other[1];
			return *this;
		}
		
		inline vec2<T> &operator++()
		{
			this->data[0]++;
			this->data[1]++;
			return *this;
		}
		
		inline vec2<T> &operator++(int)
		{
			vec2<T> out = *this;
			this->data[0]++;
			this->data[1]++;
			return out;
		}
		
		inline vec2<T> &operator--()
		{
			this->data[0]--;
			this->data[1]--;
			return *this;
		}
		
		inline vec2<T> &operator--(int)
		{
			vec2<T> out = *this;
			this->data[0]--;
			this->data[1]--;
			return out;
		}
		
		inline void set(T x, T y)
		{
			this->data[0] = x;
			this->data[1] = y;
		}
		
		inline void setAll(T value)
		{
			this->set(value, value);
		}
		
		inline void invert()
		{
			this->data[0] = -this->data[0];
			this->data[1] = -this->data[1];
		}
		
		inline vec2<T> inverse() const
		{
			return {-this->data[0], -this->data[1]};
		}
		
		inline T mag() const
		{
			return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1]);
		}
		
		inline T dot(vec2<T> const &b) const
		{
			return this->data[0] * b.x + this->data[1] * b.y;
		}
		
		inline void normalize()
		{
			T length = this->mag();
			this->data[0] /= length;
			this->data[1] /= length;
		}
		
		inline vec2<T> normalized() const
		{
			vec2<T> out;
			T length = this->mag();
			out[0] = this->data[0] / length;
			out[1] = this->data[1] / length;
			return out;
		}
		
		using value_type = T;
		
		inline size_t size() const
		{
			return 2;
		}
		
		inline std::string toString() const
		{
			std::string out = "(vec2)\n[x: ";
			out += std::to_string(this->data[0]);
			out += " y: ";
			out += std::to_string(this->data[1]);
			out += "]\n";
			return out;
		}
		
		inline void print(std::string const &name) const
		{
			printf("%s: %s\n", name.data(), this->toString().data());
		}
	};
	static_assert(std::is_pod<vec2<int32_t>>());
}
namespace IR = Iris;
