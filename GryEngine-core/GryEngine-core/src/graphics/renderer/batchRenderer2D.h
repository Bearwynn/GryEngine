#pragma once

#include "renderer2D.h"
#include "../buffers/indexBuffer.h"

namespace GryEngine {

	namespace Graphics {

#pragma region COMPILE TIME MACROS
// defined at compile time
		// -- defines the max number of sprites to be drawn
		#define RENDERER_MAX_SPRITES	60000
		// -- defines the size of a vertex in bytes
		// used for allocating buffers appropriately
		#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
		// -- defines the size of sprites (size of a vertex * 4)
		#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE * 4)
		// -- defines how much space the buffer needs
		#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
		// -- defines how many total indices there will be
		#define RENDERER_INDICES_SIZE	(RENDERER_MAX_SPRITES * 6)

		// -- defines the shader indexes for this renderer
		#define SHADER_VERTEX_INDEX 0
		#define SHADER_COLOUR_INDEX 1
#pragma endregion

		// -- Simple batch renderer --
		// renders multiple renderables per draw call
		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint			m_VertexArrayObject;
			GLuint			m_VertexBufferObject;
			VertexData*		m_Buffer;
			IndexBuffer*	m_IndexBufferObject;
			GLsizei			m_IndexCount;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			//-- used to map the buffer --
			void Begin();
			// -- used to submit renderables to the queue --
			void Submit(const Renderable2D* renderable) override;
			// -- used to unmap the buffer --
			void End();
			//-- used to perform a draw call for a batch --
			void Flush() override;

		private:
			void Initialize();
		};
	}
}