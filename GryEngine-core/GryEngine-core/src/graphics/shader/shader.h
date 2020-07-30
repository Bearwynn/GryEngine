#pragma once
#include <GL/glew.h>
#include "../../utils/file_utils.h"

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

			void Enable() const;
			void Disable() const;

		private:
			GLuint Load();
		};
	}
}