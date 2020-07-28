#pragma once

#include <math.h>
#include "maths.h"

namespace GryEngine {

	namespace Maths {

		struct Mat4x4 {
			// matrices are in columb major
			// due to OpenGL compatibility
			// to access element:
			//		elements[row + (column * width)]

			//union allows for columns to be accessed and changed as if they were Vector4's
			union {
				float elements[4 * 4];
				Vector4 column[4];
			};

			Mat4x4();
			Mat4x4(float diagonal);

			static Mat4x4 identity();

			//returns a new matrix, which is the multiplacation of two matrices
			Mat4x4& multiply(const Mat4x4& other);

			//neat operator overloads
			friend Mat4x4 operator*(Mat4x4 left, const Mat4x4& right);
			Mat4x4 operator*=(const Mat4x4& right);

			//cool projection matrices B)
			static Mat4x4 orthographic(float leftClipPlane, float rightClipPlane, float bottomClipPlane, float topClipPlane, float nearClipPlane, float farClipPlane);
			static Mat4x4 perspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane);

			//pretty sweet translation matrices
			static Mat4x4 translation(const Vector3& translation);
			static Mat4x4 rotation(float angle, const Vector3& axis);
			static Mat4x4 scale(const Vector3& scale);

		};
	}
}