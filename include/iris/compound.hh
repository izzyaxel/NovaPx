#pragma once

#include <ctgmath>
#include <limits>

namespace Iris
{
	/// Uses an int64_t for the base and a float or double offset from the base to minimize rounding errors
	template <typename T> struct Compound
	{
		int64_t base;
		T offset;
		
		/// Specialization conversion constructor
		template <typename U> Compound<T>(Compound<U> const &other)
		{
			this->base = other.base;
			this->offset = other.offset;
		}
		
		Compound(T in)
		{
			this->base = static_cast<int64_t>(std::floor(in));
			this->offset = in - this->base;
		}
		
		inline bool operator ==(Compound<T> const &other) const
		{
			return this->base == other.base && this->offset - other.offset < std::numeric_limits<T>::epsilon();
		}
		
		/// Compare inequality with another mat4x4
		inline bool operator !=(Compound<T> const &other) const
		{
			return this->base != other.base || this->offset - other.offset > std::numeric_limits<T>::epsilon();
		}
		
		inline Compound<T>(Compound<T> const &other)
		{
			this->base = other.base;
			this->offset = other.offset;
		}
		
		inline Compound<T> &operator =(Compound<T> const &other)
		{
			this->base = other.base;
			this->offset = other.offset;
			return *this;
		}
		
		inline Compound<T> operator +(Compound<T> const &other) const
		{
			Compound<T> out;
			out.base = this->base + other.base;
			out.offset = this->offset + other.offset;
			return out;
		}
		
		inline Compound<T> operator -(Compound<T> const &other) const
		{
			Compound<T> out;
			out.base = this->base - other.base;
			out.offset = this->offset - other.offset;
			return out;
		}
		
		inline Compound<T> operator *(Compound<T> const &other) const
		{
			Compound<T> out;
			out.base = this->base * other.base;
			out.offset = this->offset * other.offset;
			return out;
		}
		
		inline Compound<T> operator /(Compound<T> const &other) const
		{
			Compound<T> out;
			out.base = this->base / other.base;
			out.offset = this->offset / other.offset;
			return out;
		}
		
		inline Compound<T> operator +=(Compound<T> const &other) const
		{
			*this = *this + other;
			return this;
		}
		
		inline Compound<T> operator -=(Compound<T> const &other) const
		{
			*this = *this - other;
			return this;
		}
		
		inline Compound<T> operator *=(Compound<T> const &other) const
		{
			*this = *this * other;
			return this;
		}
		
		inline Compound<T> operator /=(Compound<T> const &other) const
		{
			*this = *this / other;
			return this;
		}
		
		/// Get the scalar value from this Compound
		inline T scalar()
		{
			return static_cast<T>(this->base + this->offset);
		}
		
		/// Get the specialized scalar value from this Compound
		template <typename U> U scalar()
		{
			return static_cast<U>(this->base + this->offset);
		}
	};
}
namespace IR = Iris;
