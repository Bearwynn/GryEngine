#include "vertexArray.h"

namespace GryEngine {

	namespace Graphics {
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID); //generate one vert array, and assign it's id


		}

		VertexArray::~VertexArray()
		{
			//delete all the buffers from memory
			for (int i = 0; i < m_Buffers.size(); i++)
			{
				delete m_Buffers[i];
			}

			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::AddBuffer(Buffer* buffer, GLuint index)
		{
			Bind();
			buffer->Bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->Unbind();
			Unbind();
		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(m_ArrayID);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}