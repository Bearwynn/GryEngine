#include "mat4.h"

namespace GryEngine {

	namespace Maths {
		
		Mat4x4::Mat4x4()
		{
			//instantiate the matrix to 0.0f
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}

		Mat4x4::Mat4x4(float diagonal)
		{
			//instantiate the matrix to 0.0f
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

			//manually set the diagonal elements to diagonal float value
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Mat4x4 Mat4x4::identity()
		{
			return Mat4x4(1.0f);
		}

		#pragma region Operation Functions
		Mat4x4& Mat4x4::multiply(const Mat4x4& other)
		{	
			Mat4x4 result;

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					result.elements[x + y * 4] = sum;
				}
			}

			return result;
		}

		Mat4x4 operator*(Mat4x4 left, const Mat4x4& right)
		{
			Mat4x4 result = left.multiply(right);

			return result;
		}

		Mat4x4 Mat4x4::operator*=(const Mat4x4& other)
		{
			return multiply(other);
		}
		#pragma endregion

		#pragma region Perspective Matrices
		Mat4x4 Mat4x4::orthographic(float leftClipPlane, float rightClipPlane, float bottomClipPlane, float topClipPlane, float nearClipPlane, float farClipPlane)
		{
			Mat4x4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (rightClipPlane - leftClipPlane);
			result.elements[1 + 1 * 4] = 2.0f / (topClipPlane - bottomClipPlane);
			result.elements[2 + 2 * 4] = 2.0f / (nearClipPlane - farClipPlane);

			result.elements[0 + 3 * 4] = (leftClipPlane + rightClipPlane) / (leftClipPlane - rightClipPlane);
			result.elements[1 + 3 * 4] = (bottomClipPlane + topClipPlane) / (bottomClipPlane - topClipPlane);
			result.elements[2 + 3 * 4] = (farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane);

			return result;
		}

		Mat4x4 Mat4x4::perspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
		{
			Mat4x4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;
			float b = (nearClipPlane + farClipPlane) / (nearClipPlane - farClipPlane);
			float c = (2.0f * nearClipPlane * farClipPlane) / (nearClipPlane - farClipPlane);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}
		#pragma endregion

		#pragma region Transformation Matrices
		Mat4x4 Mat4x4::translation(const Vector3& translation)
		{
			//[1 0 0 x]
			//[0 1 0 y]
			//[0 0 1 z]
			//[0 0 0 1]

			Mat4x4 result(1.0f);
			
			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;
			
			return result;
		}

		Mat4x4 Mat4x4::rotation(float angle, const Vector3& axis)
		{
			Mat4x4 result(1.0f);
			//too complicated for me to do example diagram, sorry lol

			float r = toRadians(angle);
			float cosine = cos(r);
			float sine = sin(r);
			float omc = 1.0f - cosine;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * x * omc + cosine;
			result.elements[1 + 0 * 4] = y * x * omc + z * sine;
			result.elements[2 + 0 * 4] = x * z * omc - z * sine;

			result.elements[0 + 1 * 4] = x * y * omc - z * sine;
			result.elements[1 + 1 * 4] = y * y * omc + cosine;
			result.elements[2 + 1 * 4] = y * z * omc + x * sine;

			result.elements[0 + 2 * 4] = x * z * omc + y * sine;
			result.elements[1 + 2 * 4] = y * z * omc - x * sine;
			result.elements[2 + 2 * 4] = z * z * omc + cosine;

			return result;
		}

		Mat4x4 Mat4x4::scale(const Vector3& scale)
		{
			//[x 0 0 0]
			//[0 y 0 0]
			//[0 0 z 0]
			//[0 0 0 1]

			Mat4x4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}
		#pragma endregion
	}
}