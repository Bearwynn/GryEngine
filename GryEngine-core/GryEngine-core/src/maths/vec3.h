#pragma once
#include <iostream>

namespace GryEngine {

	namespace Maths {

		struct Vector3
		{
			float x;
			float y;
			float z;

			Vector3();
			Vector3(const float& x, const float& y, const float& z);


			// -- functions return reference to current objects
			// -- they do not create new objects
			Vector3& add(const Vector3& other);
			Vector3& subtract(const Vector3& other);
			Vector3& multiply(const Vector3& other);
			Vector3& divide(const Vector3& other);

			// -- operator overloads --
			friend Vector3& operator+(Vector3& left, const Vector3& right);
			friend Vector3& operator-(Vector3& left, const Vector3& right);
			friend Vector3& operator*(Vector3& left, const Vector3& right);
			friend Vector3& operator/(Vector3& left, const Vector3& right);

			bool operator==(const Vector3& other);
			bool operator!=(const Vector3& other);

			Vector3& operator+=(const Vector3& other);
			Vector3& operator-=(const Vector3& other);
			Vector3& operator*=(const Vector3& other);
			Vector3& operator/=(const Vector3& other);
			
			// -- output stream operator overload --
			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		};

	}
}