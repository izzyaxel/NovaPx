#pragma once

#include "vec3.hh"
#include "general.hh"

#include <ctgmath>
#include <array>

namespace Iris
{
	template<typename T> struct quat;
	template<typename T> struct vec4;
	
	template<typename T> struct mat4x4
	{
		/// X Y Z W on each row, init to identity, row dominant
		T data[4][4]{{1, 0, 0, 0},
		             {0, 1, 0, 0},
		             {0, 0, 1, 0},
		             {0, 0, 0, 1}};
		/*using rowType = std::array<T, 4>;
		using dataType = std::array<rowType, 4>;
		dataType data;*/
		
		inline constexpr mat4x4<T>() = default;
		
		/// Specialization conversion constructor
		template<typename U> constexpr mat4x4<T>(mat4x4<U> const &other)
		{
			this->data[0][0] = other.data[0][0];
			this->data[0][1] = other.data[0][1];
			this->data[0][2] = other.data[0][2];
			this->data[0][3] = other.data[0][3];
			this->data[1][0] = other.data[1][0];
			this->data[1][1] = other.data[1][1];
			this->data[1][2] = other.data[1][2];
			this->data[1][3] = other.data[1][3];
			this->data[2][0] = other.data[2][0];
			this->data[2][1] = other.data[2][1];
			this->data[2][2] = other.data[2][2];
			this->data[2][3] = other.data[2][3];
			this->data[3][0] = other.data[3][0];
			this->data[3][1] = other.data[3][1];
			this->data[3][2] = other.data[3][2];
			this->data[3][3] = other.data[3][3];
		}
		
		constexpr inline mat4x4<T>(T x1In, T y1In, T z1In, T w1In,
		                 T x2In, T y2In, T z2In, T w2In,
		                 T x3In, T y3In, T z3In, T w3In,
		                 T x4In, T y4In, T z4In, T w4In)
		{
			this->data[0][0] = x1In;
			this->data[1][0] = y1In;
			this->data[2][0] = z1In;
			this->data[3][0] = w1In;
			this->data[0][1] = x2In;
			this->data[1][1] = y2In;
			this->data[2][1] = z2In;
			this->data[3][1] = w2In;
			this->data[0][2] = x3In;
			this->data[1][2] = y3In;
			this->data[2][2] = z3In;
			this->data[3][2] = w3In;
			this->data[0][3] = x4In;
			this->data[1][3] = y4In;
			this->data[2][3] = z4In;
			this->data[3][3] = w4In;
		}
		
		/// Convert a quaternion to a 4x4 matrix
		constexpr inline mat4x4<T>(quat<T> const &in)
		{
			T sqx = in.data[0] * in.data[0];
			T sqy = in.data[1] * in.data[1];
			T sqz = in.data[2] * in.data[2];
			T sqw = in.data[3] * in.data[3];
			this->data[0][0] = sqx - sqy - sqz + sqw;
			this->data[1][1] = -sqx + sqy - sqz + sqw;
			this->data[2][2] = -sqx - sqy + sqz + sqw;
			T t1 = in.data[0] * in.data[1];
			T t2 = in.data[2] * in.data[3];
			this->data[1][0] = ((T) 2) * (t1 + t2);
			this->data[0][1] = ((T) 2) * (t1 - t2);
			t1 = in.data[0] * in.data[2];
			t2 = in.data[1] * in.data[3];
			this->data[2][0] = ((T) 2) * (t1 - t2);
			this->data[0][2] = ((T) 2) * (t1 + t2);
			t1 = in.data[1] * in.data[2];
			t2 = in.data[0] * in.data[3];
			this->data[2][1] = ((T) 2) * (t1 + t2);
			this->data[1][2] = ((T) 2) * (t1 - t2);
		}
		
		/// Copy constructor
		inline mat4x4<T>(mat4x4<T> const &other)
		{
			memcpy(&this->data[0][0], &other[0][0], sizeof(other.data));
		}
		
		/// Copy assignment operator
		inline mat4x4<T> &operator=(mat4x4<T> const &other)
		{
			memcpy(&this->data[0][0], &other[0][0], sizeof(other.data));
			return *this;
		}
		
		/// Subscript operators
		inline T *operator[](size_t index)
		{ return this->data[index]; }
		
		inline T const *operator[](size_t index) const
		{ return this->data[index]; }
		
		/// Compare equality with another mat4x4
		inline bool operator==(mat4x4<T> const &other) const
		{
			return this->data[0][0] == other[0][0] && this->data[1][0] == other[1][0] && this->data[2][0] == other[2][0] && this->data[3][0] == other[3][0] &&
			       this->data[0][1] == other[0][1] && this->data[1][1] == other[1][1] && this->data[2][1] == other[2][1] && this->data[3][1] == other[3][1] &&
			       this->data[0][2] == other[0][2] && this->data[1][2] == other[1][2] && this->data[2][2] == other[2][2] && this->data[3][2] == other[3][2] &&
			       this->data[0][3] == other[0][3] && this->data[1][3] == other[1][3] && this->data[2][3] == other[2][3] && this->data[3][3] == other[3][3];
		}
		
		/// Compare inequality with another mat4x4
		inline bool operator!=(mat4x4<T> const &other) const
		{
			return this->data[0][0] != other[0][0] || this->data[1][0] != other[1][0] || this->data[2][0] != other[2][0] || this->data[3][0] != other[3][0] ||
			       this->data[0][1] != other[0][1] || this->data[1][1] != other[1][1] || this->data[2][1] != other[2][1] || this->data[3][1] != other[3][1] ||
			       this->data[0][2] != other[0][2] || this->data[1][2] != other[1][2] || this->data[2][2] != other[2][2] || this->data[3][2] != other[3][2] ||
			       this->data[0][3] != other[0][3] || this->data[1][3] != other[1][3] || this->data[2][3] != other[2][3] || this->data[3][3] != other[3][3];
		}
		
		/// Multiply this 4x4 matrix by another
		inline mat4x4<T> operator*(mat4x4<T> const &other) const
		{
			mat4x4<T> out;
			out[0][0] = this->data[0][0] * other[0][0] + this->data[0][1] * other[1][0] + this->data[0][2] * other[2][0] + this->data[0][3] * other[3][0];
			out[0][1] = this->data[0][0] * other[0][1] + this->data[0][1] * other[1][1] + this->data[0][2] * other[2][1] + this->data[0][3] * other[3][1];
			out[0][2] = this->data[0][0] * other[0][2] + this->data[0][1] * other[1][2] + this->data[0][2] * other[2][2] + this->data[0][3] * other[3][2];
			out[0][3] = this->data[0][0] * other[0][3] + this->data[0][1] * other[1][3] + this->data[0][2] * other[2][3] + this->data[0][3] * other[3][3];
			out[1][0] = this->data[1][0] * other[0][0] + this->data[1][1] * other[1][0] + this->data[1][2] * other[2][0] + this->data[1][3] * other[3][0];
			out[1][1] = this->data[1][0] * other[0][1] + this->data[1][1] * other[1][1] + this->data[1][2] * other[2][1] + this->data[1][3] * other[3][1];
			out[1][2] = this->data[1][0] * other[0][2] + this->data[1][1] * other[1][2] + this->data[1][2] * other[2][2] + this->data[1][3] * other[3][2];
			out[1][3] = this->data[1][0] * other[0][3] + this->data[1][1] * other[1][3] + this->data[1][2] * other[2][3] + this->data[1][3] * other[3][3];
			out[2][0] = this->data[2][0] * other[0][0] + this->data[2][1] * other[1][0] + this->data[2][2] * other[2][0] + this->data[2][3] * other[3][0];
			out[2][1] = this->data[2][0] * other[0][1] + this->data[2][1] * other[1][1] + this->data[2][2] * other[2][1] + this->data[2][3] * other[3][1];
			out[2][2] = this->data[2][0] * other[0][2] + this->data[2][1] * other[1][2] + this->data[2][2] * other[2][2] + this->data[2][3] * other[3][2];
			out[2][3] = this->data[2][0] * other[0][3] + this->data[2][1] * other[1][3] + this->data[2][2] * other[2][3] + this->data[2][3] * other[3][3];
			out[3][0] = this->data[3][0] * other[0][0] + this->data[3][1] * other[1][0] + this->data[3][2] * other[2][0] + this->data[3][3] * other[3][0];
			out[3][1] = this->data[3][0] * other[0][1] + this->data[3][1] * other[1][1] + this->data[3][2] * other[2][1] + this->data[3][3] * other[3][1];
			out[3][2] = this->data[3][0] * other[0][2] + this->data[3][1] * other[1][2] + this->data[3][2] * other[2][2] + this->data[3][3] * other[3][2];
			out[3][3] = this->data[3][0] * other[0][3] + this->data[3][1] * other[1][3] + this->data[3][2] * other[2][3] + this->data[3][3] * other[3][3];
			return out;
		}
		
		inline vec4<T> operator*(vec4<T> const &vec)
		{
			return vec4<T>{
					vec[0] * this->data[0][0] + vec[1] * this->data[1][0] + vec[2] * this->data[2][0] + vec[3] * this->data[3][0],
					vec[0] * this->data[0][1] + vec[1] * this->data[1][1] + vec[2] * this->data[2][1] + vec[3] * this->data[3][1],
					vec[0] * this->data[0][2] + vec[1] * this->data[1][2] + vec[2] * this->data[2][2] + vec[3] * this->data[3][2],
					vec[0] * this->data[0][3] + vec[1] * this->data[1][3] + vec[2] * this->data[2][3] + vec[3] * this->data[3][3],
			};
		}
		
		/// Get the determinant of this 4x4 matrix
		inline T determinant() const
		{
			return
					this->data[0][3] * this->data[1][2] * this->data[2][1] * this->data[3][0] - this->data[0][2] * this->data[1][3] * this->data[2][1] * this->data[3][0] -
					this->data[0][3] * this->data[1][1] * this->data[2][2] * this->data[3][0] + this->data[0][1] * this->data[1][3] * this->data[2][2] * this->data[3][0] +
					this->data[0][2] * this->data[1][1] * this->data[2][3] * this->data[3][0] - this->data[0][1] * this->data[1][2] * this->data[2][3] * this->data[3][0] -
					this->data[0][3] * this->data[1][2] * this->data[2][0] * this->data[3][1] + this->data[0][2] * this->data[1][3] * this->data[2][0] * this->data[3][1] +
					this->data[0][3] * this->data[1][0] * this->data[2][2] * this->data[3][1] - this->data[0][0] * this->data[1][3] * this->data[2][2] * this->data[3][1] -
					this->data[0][2] * this->data[1][0] * this->data[2][3] * this->data[3][1] + this->data[0][0] * this->data[1][2] * this->data[2][3] * this->data[3][1] +
					this->data[0][3] * this->data[1][1] * this->data[2][0] * this->data[3][2] - this->data[0][1] * this->data[1][3] * this->data[2][0] * this->data[3][2] -
					this->data[0][3] * this->data[1][0] * this->data[2][1] * this->data[3][2] + this->data[0][0] * this->data[1][3] * this->data[2][1] * this->data[3][2] +
					this->data[0][1] * this->data[1][0] * this->data[2][3] * this->data[3][2] - this->data[0][0] * this->data[1][1] * this->data[2][3] * this->data[3][2] -
					this->data[0][2] * this->data[1][1] * this->data[2][0] * this->data[3][3] + this->data[0][1] * this->data[1][2] * this->data[2][0] * this->data[3][3] +
					this->data[0][2] * this->data[1][0] * this->data[2][1] * this->data[3][3] - this->data[0][0] * this->data[1][2] * this->data[2][1] * this->data[3][3] -
					this->data[0][1] * this->data[1][0] * this->data[2][2] * this->data[3][3] + this->data[0][0] * this->data[1][1] * this->data[2][2] * this->data[3][3];
		}
		
		//row-column reversed
		/// Invert this mat4x4
		inline void invert()
		{
			T A2323 = this->data[2][2] * this->data[3][3] - this->data[3][2] * this->data[2][3];
			T A1323 = this->data[1][2] * this->data[3][3] - this->data[3][2] * this->data[1][3];
			T A1223 = this->data[1][2] * this->data[2][3] - this->data[2][2] * this->data[1][3];
			T A0323 = this->data[0][2] * this->data[3][3] - this->data[3][2] * this->data[0][3];
			T A0223 = this->data[0][2] * this->data[2][3] - this->data[2][2] * this->data[0][3];
			T A0123 = this->data[0][2] * this->data[1][3] - this->data[1][2] * this->data[0][3];
			T A2313 = this->data[2][1] * this->data[3][3] - this->data[3][1] * this->data[2][3];
			T A1313 = this->data[1][1] * this->data[3][3] - this->data[3][1] * this->data[1][3];
			T A1213 = this->data[1][1] * this->data[2][3] - this->data[2][1] * this->data[1][3];
			T A2312 = this->data[2][1] * this->data[3][2] - this->data[3][1] * this->data[2][2];
			T A1312 = this->data[1][1] * this->data[3][2] - this->data[3][1] * this->data[1][2];
			T A1212 = this->data[1][1] * this->data[2][2] - this->data[2][1] * this->data[1][2];
			T A0313 = this->data[0][1] * this->data[3][3] - this->data[3][1] * this->data[0][3];
			T A0213 = this->data[0][1] * this->data[2][3] - this->data[2][1] * this->data[0][3];
			T A0312 = this->data[0][1] * this->data[3][2] - this->data[3][1] * this->data[0][2];
			T A0212 = this->data[0][1] * this->data[2][2] - this->data[2][1] * this->data[0][2];
			T A0113 = this->data[0][1] * this->data[1][3] - this->data[1][1] * this->data[0][3];
			T A0112 = this->data[0][1] * this->data[1][2] - this->data[1][1] * this->data[0][2];
			
			T det = + data[0][0] * (data[1][1] * A2323 - data[2][1] * A1323 + data[3][1] * A1223)
					- data[1][0] * (data[0][1] * A2323 - data[2][1] * A0323 + data[3][1] * A0223)
					+ data[2][0] * (data[0][1] * A1323 - data[1][1] * A0323 + data[3][1] * A0123)
					- data[3][0] * (data[0][1] * A1223 - data[1][1] * A0223 + data[2][1] * A0123);
			det = static_cast<T>(1) / det;
			
			*this = mat4x4<T>{
					det *   (data[1][1] * A2323 - data[2][1] * A1323 + data[3][1] * A1223),
					det * - (data[1][0] * A2323 - data[2][0] * A1323 + data[3][0] * A1223),
					det *   (data[1][0] * A2313 - data[2][0] * A1313 + data[3][0] * A1213),
					det * - (data[1][0] * A2312 - data[2][0] * A1312 + data[3][0] * A1212),
					det * - (data[0][1] * A2323 - data[2][1] * A0323 + data[3][1] * A0223),
					det *   (data[0][0] * A2323 - data[2][0] * A0323 + data[3][0] * A0223),
					det * - (data[0][0] * A2313 - data[2][0] * A0313 + data[3][0] * A0213),
					det *   (data[0][0] * A2312 - data[2][0] * A0312 + data[3][0] * A0212),
					det *   (data[0][1] * A1323 - data[1][1] * A0323 + data[3][1] * A0123),
					det * - (data[0][0] * A1323 - data[1][0] * A0323 + data[3][0] * A0123),
					det *   (data[0][0] * A1313 - data[1][0] * A0313 + data[3][0] * A0113),
					det * - (data[0][0] * A1312 - data[1][0] * A0312 + data[3][0] * A0112),
					det * - (data[0][1] * A1223 - data[1][1] * A0223 + data[2][1] * A0123),
					det *   (data[0][0] * A1223 - data[1][0] * A0223 + data[2][0] * A0123),
					det * - (data[0][0] * A1213 - data[1][0] * A0213 + data[2][0] * A0113),
					det *   (data[0][0] * A1212 - data[1][0] * A0212 + data[2][0] * A0112),
				};
		}
		
		//row-column reversed
		/// Get a new inverted mat4x4 from this one
		inline mat4x4<T> inverse() const
		{
			T A2323 = this->data[2][2] * this->data[3][3] - this->data[3][2] * this->data[2][3];
			T A1323 = this->data[1][2] * this->data[3][3] - this->data[3][2] * this->data[1][3];
			T A1223 = this->data[1][2] * this->data[2][3] - this->data[2][2] * this->data[1][3];
			T A0323 = this->data[0][2] * this->data[3][3] - this->data[3][2] * this->data[0][3];
			T A0223 = this->data[0][2] * this->data[2][3] - this->data[2][2] * this->data[0][3];
			T A0123 = this->data[0][2] * this->data[1][3] - this->data[1][2] * this->data[0][3];
			T A2313 = this->data[2][1] * this->data[3][3] - this->data[3][1] * this->data[2][3];
			T A1313 = this->data[1][1] * this->data[3][3] - this->data[3][1] * this->data[1][3];
			T A1213 = this->data[1][1] * this->data[2][3] - this->data[2][1] * this->data[1][3];
			T A2312 = this->data[2][1] * this->data[3][2] - this->data[3][1] * this->data[2][2];
			T A1312 = this->data[1][1] * this->data[3][2] - this->data[3][1] * this->data[1][2];
			T A1212 = this->data[1][1] * this->data[2][2] - this->data[2][1] * this->data[1][2];
			T A0313 = this->data[0][1] * this->data[3][3] - this->data[3][1] * this->data[0][3];
			T A0213 = this->data[0][1] * this->data[2][3] - this->data[2][1] * this->data[0][3];
			T A0312 = this->data[0][1] * this->data[3][2] - this->data[3][1] * this->data[0][2];
			T A0212 = this->data[0][1] * this->data[2][2] - this->data[2][1] * this->data[0][2];
			T A0113 = this->data[0][1] * this->data[1][3] - this->data[1][1] * this->data[0][3];
			T A0112 = this->data[0][1] * this->data[1][2] - this->data[1][1] * this->data[0][2];
			
			T det = + data[0][0] * (data[1][1] * A2323 - data[2][1] * A1323 + data[3][1] * A1223)
			        - data[1][0] * (data[0][1] * A2323 - data[2][1] * A0323 + data[3][1] * A0223)
			        + data[2][0] * (data[0][1] * A1323 - data[1][1] * A0323 + data[3][1] * A0123)
			        - data[3][0] * (data[0][1] * A1223 - data[1][1] * A0223 + data[2][1] * A0123);
			det = static_cast<T>(1) / det;
			
			return mat4x4<T>{
					det *   (data[1][1] * A2323 - data[2][1] * A1323 + data[3][1] * A1223),
					det * - (data[1][0] * A2323 - data[2][0] * A1323 + data[3][0] * A1223),
					det *   (data[1][0] * A2313 - data[2][0] * A1313 + data[3][0] * A1213),
					det * - (data[1][0] * A2312 - data[2][0] * A1312 + data[3][0] * A1212),
					det * - (data[0][1] * A2323 - data[2][1] * A0323 + data[3][1] * A0223),
					det *   (data[0][0] * A2323 - data[2][0] * A0323 + data[3][0] * A0223),
					det * - (data[0][0] * A2313 - data[2][0] * A0313 + data[3][0] * A0213),
					det *   (data[0][0] * A2312 - data[2][0] * A0312 + data[3][0] * A0212),
					det *   (data[0][1] * A1323 - data[1][1] * A0323 + data[3][1] * A0123),
					det * - (data[0][0] * A1323 - data[1][0] * A0323 + data[3][0] * A0123),
					det *   (data[0][0] * A1313 - data[1][0] * A0313 + data[3][0] * A0113),
					det * - (data[0][0] * A1312 - data[1][0] * A0312 + data[3][0] * A0112),
					det * - (data[0][1] * A1223 - data[1][1] * A0223 + data[2][1] * A0123),
					det *   (data[0][0] * A1223 - data[1][0] * A0223 + data[2][0] * A0123),
					det * - (data[0][0] * A1213 - data[1][0] * A0213 + data[2][0] * A0113),
					det *   (data[0][0] * A1212 - data[1][0] * A0212 + data[2][0] * A0112),
			};
		}
		
		/// Transpose this 4x4 matrix
		inline mat4x4<T> transpose() const
		{
			mat4x4<T> out;
			out[0][0] = this->data[0][0];
			out[0][1] = this->data[1][0];
			out[0][2] = this->data[2][0];
			out[0][3] = this->data[3][0];
			out[1][0] = this->data[0][1];
			out[1][1] = this->data[1][1];
			out[1][2] = this->data[2][1];
			out[1][3] = this->data[3][1];
			out[2][0] = this->data[0][2];
			out[2][1] = this->data[1][2];
			out[2][2] = this->data[2][2];
			out[2][3] = this->data[3][2];
			out[3][0] = this->data[0][3];
			out[3][1] = this->data[1][3];
			out[3][2] = this->data[2][3];
			out[3][3] = this->data[3][3];
			return out;
		}
		
		using value_type = T;
		
		inline size_t size() const
		{
			return 16;
		}
		
		/// Compose a string out of this mat4x4's values
		inline std::string toString() const
		{
			std::string out = "(mat4x4)\n";
			for (int i = 0; i < 4; i++)
			{
				out += "[";
				for (int j = 0; j < 4; j++)
				{
					switch (j)
					{
						case 0:
							out += "x: ";
							break;
						case 1:
							out += "y: ";
							break;
						case 2:
							out += "z: ";
							break;
						case 3:
							out += "w: ";
							break;
						default:
							break;
					}
					out += std::to_string(this->data[i][j]);
					if (j < 3) out += " ";
				}
				out += "]\n";
			}
			return out;
		}
		
		/// Print this mat4x4 with printf
		inline void print(std::string const &name) const
		{
			printf("%s: %s\n", name.data(), this->toString().data());
		}
	};
	
	template <typename T> inline mat4x4<T> translateMat(vec3<T> const &in)
	{
		mat4x4<T> out{};
		out[3][0] = in[0];
		out[3][1] = in[1];
		out[3][2] = in[2];
		return out;
	}
	
	template <typename T> inline mat4x4<T> rotateMat(quat<T> const &in)
	{
		return mat4x4<T>{in};
	}
	
	/// Convert a vec3 scale into a mat4x4 representation
	template <typename T> inline mat4x4<T> scaleMat(vec3<T> const &scale)
	{
		mat4x4<T> out{};
		out[0][0] = scale[0];
		out[1][1] = scale[1];
		out[2][2] = scale[2];
		return out;
	}
	
	template <typename T> inline mat4x4<T> scaleMat(T scalar)
	{
		mat4x4<T> out;
		out[0][0] = scalar;
		out[1][1] = scalar;
		out[2][2] = scalar;
		return out;
	}
	
	template <typename T> inline mat4x4<T> modelMatrix(vec3<T> const &position, quat<T> const &rotation, vec3<T> const &scale)
	{
		mat4x4<T> t = translateMat(position);
		mat4x4<T> r = rotateMat(rotation);
		mat4x4<T> s = scaleMat(scale);
		return s * r * t;
	}
	
	template <typename T> inline mat4x4<T> modelMatrixText(vec3<T> const &position, quat<T> const &rotation, vec3<T> const &scale)
	{
		mat4x4<T> t = translateMat(position);
		mat4x4<T> r = rotateMat(rotation);
		mat4x4<T> s = scaleMat(scale);
		return s * t * r;
	}
	
	template <typename T> inline mat4x4<T> modelMatrix(vec3<T> const &position, vec3<T> const &origin, quat<T> const &rotation, vec3<T> const &scale)
	{
		mat4x4<T> tOffset = translateMat(origin);
		mat4x4<T> r = rotateMat(rotation);
		mat4x4<T> t = translateMat(position);
		mat4x4<T> s = scaleMat(scale);
		return s * tOffset * r * t;
	}
	
	template <typename T> inline mat4x4<T> viewMatrix(quat<T> const &cameraRotation, vec3<T> const &cameraPosition)
	{
		mat4x4<T> rot = mat4x4<T>{cameraRotation.inverse()};
		mat4x4<T> trans = translateMat(cameraPosition.inverse());
		return trans * rot;
	}
	
	template <typename T> inline mat4x4<T> perspectiveProjectionMatrix(T fov, T nearPlane, T farPlane, uint32_t width, uint32_t height)
	{
		T halfFOV = static_cast<T>(1) / std::tan(static_cast<T>(0.5) * degToRad(fov));
		mat4x4<T> out{};
		out[0][0] = halfFOV * (static_cast<T>(height) / static_cast<T>(width));
		out[1][1] = halfFOV;
		out[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane);
		out[2][3] = static_cast<T>(1);
		out[3][2] = -(static_cast<T>(2) * farPlane * nearPlane) / (farPlane - nearPlane);
		out[3][3] = 0;
		return out;
	}
	
	template <typename T> inline mat4x4<T> orthoProjectionMatrix(T left, T right, T top, T bottom, T zNear, T zFar)
	{
		mat4x4<T> out{};
		out[0][0] = static_cast<T>(2) / (right - left);
		out[1][1] = static_cast<T>(2) / (top - bottom);
		out[2][2] = -static_cast<T>(2) / (zFar - zNear);
		out[3][0] = -(right + left) / (right - left);
		out[3][1] = -(top + bottom) / (top - bottom);
		out[3][2] = -(zFar + zNear) / (zFar - zNear);
		return out;
	}
	
	template <typename T> inline mat4x4<T> modelViewProjectionMatrix(mat4x4<T> const &model, mat4x4<T> const &view, mat4x4<T> const &projection)
	{
		return model * view * projection;
	}
}
namespace IR = Iris;
