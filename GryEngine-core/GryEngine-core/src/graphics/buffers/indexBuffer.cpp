#include "indexBuffer.h"

namespace GryEngine {

	namespace Graphics {

		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
		{
			m_Count = count;


			glGenBuffers(1, &m_BufferID);								//generate one buffer, and assign it's ID to BufferID
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);			//bind an array of data to bufferID
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,						//the buffer type is an array
						count * sizeof(GLushort),						//how big the buffer should be in bytes
						data,											//the data to be added to the buffer
						GL_STATIC_DRAW);								//means the data will not be changed, it's static
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);					//unbind everything
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);			//bind an array of data to bufferID
		}

		void IndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);					//unbind everything
		}
	}
}