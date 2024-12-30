#pragma once
#include <type_traits>
#include <concepts>

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
struct Rectangle
{
	Rectangle(T x, T y, T width, T height)
		: X(x), Y(y), Width(width), Height(height) { }

	void Move(uint32_t x, uint32_t y) { X = x; Y = y; }
public:
	T X{ 0 }, Y{ 0 };
	T Width{ 0 }, Height{ 0 };
};

using FRectangle = Rectangle<float>;
using IRectangle = Rectangle<uint32_t>;

