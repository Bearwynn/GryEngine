#include "batchRenderer2D.h"

namespace GryEngine {

	namespace Graphics {

		BatchRenderer2D::BatchRenderer2D()
		{
			Initialize();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IndexBufferObject;
			glDeleteBuffers(1, &m_VertexBufferObject);
		}

		void BatchRenderer2D::Initialize()
		{
			// -- GENERATE --
			glGenVertexArrays(1, &m_VertexArrayObject);
			glGenBuffers(1, &m_VertexBufferObject);

			// -- BIND TO OpenGL --
			glBindVertexArray(m_VertexArrayObject);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);

			// -- ATTACH DATA --
			//bind the 'VertexData' struct to the buffer
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW); 
			
			// -- DEFINE THE STRUCTURE OF THE BUFFER --
			/*glVertexAttribPointer(index,					Specifies the index of the generic vertex attribute to be modified.
									size,					Specifies the number of components per generic vertex attribute.
									type,					Specifies the data type of each component in the array.
									normalized,				Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
									stride,					Specifies the byte offset between consecutive generic vertex attributes.
									pointer);				Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. 
			*/

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 
								  3, 
								  GL_FLOAT, 
								  GL_FALSE, 
								  RENDERER_VERTEX_SIZE,
								  (const GLvoid*)0);

			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			glVertexAttribPointer(SHADER_COLOUR_INDEX,
								  4,
								  GL_FLOAT,
								  GL_FALSE,
								  RENDERER_VERTEX_SIZE,
								  (const GLvoid*)(3 * sizeof(GLfloat)));

			// -- UNBIND FROM OpenGL --
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// -- GENERATE INDEXES --
			GLushort indices[RENDERER_INDICES_SIZE];				//generate array of GLushort of indices size
			int offset = 0;											//offset of vertex
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)		//iterate through, changing index 6 at a time (6 indices per sprite)
			{
				//-- first triangle indices --
				indices[  i  ]	= offset + 0;
				indices[i + 1]	= offset + 1;
				indices[i + 2]	= offset + 2;

				//-- second triangle indices --
				indices[i + 3]	= offset + 2;
				indices[i + 4]	= offset + 3;
				indices[i + 5]	= offset + 0;

				offset += 4;						//only four vertices, not 6, so add 4 to offset
			}

			// -- GENERATE INDEX BUFFER --
			m_IndexBufferObject = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			// -- UNBIND VERTEX ARRAY --
			glBindVertexArray(0);
		}

		void BatchRenderer2D::Begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); //returns a pointer to the very first byte of the buffer
		}

		void BatchRenderer2D::Submit(const Renderable2D* renderable)
		{
			const Maths::Vector3& position	= renderable->GetPosition();
			const Maths::Vector2& size		= renderable->GetSize();
			const Maths::Vector4& colour	= renderable->GetColour();

			//Set First Index
			m_Buffer->vertex = position;
			m_Buffer->colour = colour;
			m_Buffer++;

			//Set Second Index
			m_Buffer->vertex = Maths::Vector3(position.x, position.y + size.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			//Set Third Index
			m_Buffer->vertex = Maths::Vector3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			//Set Fourth Index
			m_Buffer->vertex = Maths::Vector3(position.x + size.x, position.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			// -- INCREMENT INDEX COUNT --
			m_IndexCount += 6;
		}
		 
		void BatchRenderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer2D::Flush()
		{
			// -- BIND --
			glBindVertexArray(m_VertexArrayObject);
			m_IndexBufferObject->Bind();

			// -- DRAW --
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

			// -- UNBIND --
			m_IndexBufferObject->Unbind();
			glBindVertexArray(0);

			// -- RESET INDEX COUNT --
			m_IndexCount = 0;
		}
	}
}