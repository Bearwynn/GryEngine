#pragma once
#include <GL/glew.h>

namespace GryEngine {

	namespace Graphics {

		//an OpenGL Buffer class
		class Buffer {
		private:
			GLuint m_BufferID;			//ID that openGL provides when buffer is created
			GLuint m_ComponentCount;	//how many components (vec3, vec4's etc) are in the buffer

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void Bind() const;
			void Unbind() const;

			inline GLuint GetComponentCount() const { return m_ComponentCount; };
		};

	}
}