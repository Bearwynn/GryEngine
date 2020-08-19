#pragma once
#include "renderable2D.h"

#include "../buffers/buffer.h"
#include "../buffers/indexBuffer.h"
#include "../buffers/vertexArray.h"

#include "../shader/shader.h"

namespace GryEngine {

	namespace Graphics {

		class  StaticSprite : public Renderable2D
		{
		private:
			// -- Shader --
			Shader& m_Shader;

			// -- Buffers --
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
		public:
			StaticSprite(float x, float y, float width, float height, Maths::Vector4& colour, Shader& shader);
			~StaticSprite();

			// -- Get Functions --
			inline Shader& GetShader() const { return m_Shader; };
			inline const VertexArray* GetVertexArray() const { return m_VertexArray; };
			inline const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };
		};

	}
}