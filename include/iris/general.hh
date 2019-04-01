#pragma once

#include <vector>
#include <ctgmath>

namespace Iris
{
	/// PI constant
	template<typename T> T constexpr pi = static_cast<T>(3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145649L);
	
	template<typename T> int32_t sign(T in)
	{
		return (in > static_cast<T>(0)) - (in < static_cast<T>(0));
	}

	/// Find a point along a sine wave between a min and max value
	template<typename T> T boundedSine(T max, T min, T time)
	{
		return ((max - min) * std::sin(time) + max + min) / static_cast<T>(2);
	}

	/// Convert a degree angle into a radian angle
	template<typename T> T degToRad(T degree)
	{
		return degree * (pi<T> / static_cast<T>(180));
	}

	/// Convert a radian angle into a degree angle
	template<typename T> T radToDeg(T radian)
	{
		return radian / (pi<T> / static_cast<T>(180));
	}
	
	/// A pascal triangle, typically used for finding weights, eg for blurring algorithms
	template<typename T> struct PascalTriangle
	{
		std::vector<std::vector<T>> rows{{1}};
		
		inline PascalTriangle(size_t rows)
		{
			for (size_t i = 1; i < rows + 1; i++) generateRow();
		}
		
		std::vector<T> const &row(size_t row)
		{
			for (size_t i = rows.size(); i < row + 1; i++) generateRow();
			return rows[row];
		}
	
	protected:
		inline void generateRow()
		{
			auto &lastRow = rows.back();
			std::vector<T> newRow{static_cast<T>(1)};
			newRow.resize(rows.size());
			for (size_t i = 1; i < rows.size(); i++) newRow[i] = lastRow[i - 1] + lastRow[i];
			newRow.push_back(static_cast<T>(1));
			rows.push_back(newRow);
		}
	};
}
namespace IR = Iris;
