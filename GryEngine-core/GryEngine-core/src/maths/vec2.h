#pragma once
#include <iostream>

namespace GryEngine {

	namespace Maths {

		struct Vector2
		{
			float x;
			float y;

			Vector2();
			Vector2(const float& x, const float& y);


			// -- functions return reference to current objects
			// -- they do not create new objects
			Vector2& add(const Vector2& other);
			Vector2& subtract(const Vector2& other);
			Vector2& multiply(const Vector2& other);
			Vector2& divide(const Vector2& other);

			// -- operator overloads --
			friend Vector2& operator+(Vector2 left, const Vector2& right);
			friend Vector2& operator-(Vector2 left, const Vector2& right);
			friend Vector2& operator*(Vector2 left, const Vector2& right);
			friend Vector2& operator/(Vector2 left, const Vector2& right);

			bool operator==(const Vector2& other);
			bool operator!=(const Vector2& other);

			Vector2& operator+=(const Vector2& other);
			Vector2& operator-=(const Vector2& other);
			Vector2& operator*=(const Vector2& other);
			Vector2& operator/=(const Vector2& other);
			
			// -- output stream operator overload --
			friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		};

	}
}