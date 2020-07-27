#pragma once
#include <iostream>

namespace GryEngine {

	namespace Maths {

		struct Vector4
		{
			float x;
			float y;
			float z;
			float w;

			Vector4();
			Vector4(const float& x, const float& y, const float& z, const float& w);


			// -- functions return reference to current objects
			// -- they do not create new objects
			Vector4& add(const Vector4& other);
			Vector4& subtract(const Vector4& other);
			Vector4& multiply(const Vector4& other);
			Vector4& divide(const Vector4& other);

			// -- operator overloads --
			friend Vector4& operator+(Vector4& left, const Vector4& right);
			friend Vector4& operator-(Vector4& left, const Vector4& right);
			friend Vector4& operator*(Vector4& left, const Vector4& right);
			friend Vector4& operator/(Vector4& left, const Vector4& right);

			bool operator==(const Vector4& other);
			bool operator!=(const Vector4& other);

			Vector4& operator+=(const Vector4& other);
			Vector4& operator-=(const Vector4& other);
			Vector4& operator*=(const Vector4& other);
			Vector4& operator/=(const Vector4& other);
			
			// -- output stream operator overload --
			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
		};

	}
}