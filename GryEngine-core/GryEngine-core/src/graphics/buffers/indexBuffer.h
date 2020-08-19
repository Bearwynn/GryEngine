#pragma once
#include <GL/glew.h>

namespace GryEngine {

	namespace Graphics {

		//an OpenGL Buffer class
		class IndexBuffer {
		private:
			GLuint m_BufferID;			//ID that openGL provides when buffer is created
			GLuint m_Count;				//a count of how many indices there are (for draw call)

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			~IndexBuffer();

			void Bind() const;
			void Unbind() const;

			inline GLuint GetCount() const { return m_Count; };
		};

	}
}