#include "vec3.h"

namespace GryEngine {

	namespace Maths {

		// -- default constructor --
		Vector3::Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		// -- overload constructor --
		Vector3::Vector3(const float& x, const float& y, const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		#pragma region Member Functions
		// -- Add Function --
		Vector3& Vector3::add(const Vector3& other)
		{
			// -- perform additions --
			x += other.x;
			y += other.y;
			z += other.z;

			// -- return the current object --
			return *this;
		}

		//-- Subtract Function --
		Vector3& Vector3::subtract(const Vector3& other)
		{
			// -- perform subtractions --
			x -= other.x;
			y -= other.y;
			z -= other.z;

			// -- return the current object --
			return *this;
		}

		//-- Multiply Function --
		Vector3& Vector3::multiply(const Vector3& other)
		{
			// -- perform multiplication --
			x *= other.x;
			y *= other.y;
			z *= other.z;

			// -- return the current object --
			return *this;
		}

		//-- Divide Function --
		Vector3& Vector3::divide(const Vector3& other)
		{
			// -- perform divisions --
			x /= other.x;
			y /= other.y;
			z /= other.z;

			// -- return the current object --
			return *this;
		}
		#pragma endregion
		 
		#pragma region Operator Overloads
		// -- Operator Overloads --
		Vector3& operator+(Vector3 left, const Vector3& right)
		{
			return left.add(right);
		}

		Vector3& operator-(Vector3 left, const Vector3& right)
		{
			return left.subtract(right);
		}

		Vector3& operator*(Vector3 left, const Vector3& right)
		{
			return left.multiply(right);
		}

		Vector3& operator/(Vector3 left, const Vector3& right)
		{
			return left.divide(right);
		}

		bool Vector3::operator==(const Vector3& other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vector3::operator!=(const Vector3& other)
		{
			return !(*this == other);
		}

		Vector3& Vector3::operator+=(const Vector3& other)
		{
			return add(other);
		}

		Vector3& Vector3::operator-=(const Vector3& other)
		{
			return subtract(other);
		}

		Vector3& Vector3::operator*=(const Vector3& other)
		{
			return multiply(other);
		}

		Vector3& Vector3::operator/=(const Vector3& other)
		{
			return divide(other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
		{
			stream << "Vector3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";

			return stream;
		}
		#pragma endregion
	}
}