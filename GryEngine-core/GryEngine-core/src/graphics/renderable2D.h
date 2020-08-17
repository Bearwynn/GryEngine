#pragma once
#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"

#include "shader/shader.h"
#include "../maths/maths.h"

namespace GryEngine {

	namespace Graphics {


		class Renderable2D
		{
		protected:
			// -- Vector Data --
			Maths::Vector3 m_Position;
			Maths::Vector2 m_Size;
			Maths::Vector4 m_Colour;

			// -- Shader --
			Shader& m_Shader;

			// -- Buffers --
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;

		public:
			Renderable2D(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 colour, Shader& shader)
				: m_Position(position), m_Size(size), m_Colour(colour), m_Shader(shader) 
			{
				// -- vertices GLfloat array based on size of object --
				GLfloat vertices[] =
				{
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				// -- indices array for coordinate reuse --
				GLushort indices[] =
				{
					0, 1,
					2, 2,
					3, 0
				};

				// -- colour GLfloat array to store object colour --
				GLfloat colours[] =
				{
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w
				};

				m_VertexArray = new VertexArray();								//generate new vertex array
				m_VertexArray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);	//add the vertices to the buffer
				m_VertexArray->AddBuffer(new Buffer(colours, 4 * 4, 4), 1);		//add the colours to the buffer

				m_IndexBuffer = new IndexBuffer(indices, 6);					//create a new index buffer with the indices
			
			};

			~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			};

			inline const Maths::Vector3& GetPosition() const { return m_Position; };
			inline const Maths::Vector2& GetSize() const { return m_Size; };
			inline const Maths::Vector4& GetColour() const { return m_Colour; };

			inline Shader& GetShader() const { return m_Shader; };

			inline const VertexArray* GetVertexArray() const { return m_VertexArray; };
			inline const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };
		};

	}
}