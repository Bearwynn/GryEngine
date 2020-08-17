#pragma once
#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace GryEngine {

	namespace Graphics {

		class VertexArray {
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers; //a vector to store pointers to buffers

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer* buffer, GLuint index);	//add a buffer to the array
			void Bind() const;
			void Unbind() const;
		};

	}
}