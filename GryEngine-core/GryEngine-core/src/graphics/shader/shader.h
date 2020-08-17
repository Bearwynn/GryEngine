#pragma once
#include <GL/glew.h>
#include "../../utils/file_utils.h"
#include "../../maths/maths.h"

namespace GryEngine {

	namespace Graphics {

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char* m_VertPath;
			const char* m_FragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void SetUniform1float(const GLchar* name, float value);
			void SetUniform1int(const GLchar* name, int value);
			void SetUniform2float(const GLchar* name, const Maths::Vector2& vector);
			void SetUniform3float(const GLchar* name, const Maths::Vector3& vector);
			void SetUniform4float(const GLchar* name, const Maths::Vector4& vector);
			void SetUniformMat4x4(const GLchar* name, const Maths::Mat4x4& matrix);

			void Enable() const;
			void Disable() const;

		private:
			GLuint Load();
			GLint GetUniformLocation(const GLchar* name);
		};
	}
}