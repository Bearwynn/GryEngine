#include "buffer.h"


namespace GryEngine {

	namespace Graphics {

		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
		{
			m_ComponentCount = componentCount;


			glGenBuffers(1, &m_BufferID);				//generate one buffer, and assign it's ID to BufferID
			
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);	//bind an array of data to bufferID

			glBufferData(GL_ARRAY_BUFFER,				//the buffer type is an array
						count * sizeof(GLfloat),		//how big the buffer should be in bytes
						data,							//the data to be added to the buffer
						GL_STATIC_DRAW);				//means the data will not be changed, it's static
		
			glBindBuffer(GL_ARRAY_BUFFER, 0);			//unbind everything
		}

		void Buffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);	//bind an array of data to bufferID
		}

		void Buffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);			//unbind everything
		}
	}
}