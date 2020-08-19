#pragma once

#include <deque>
#include "renderer2D.h"
#include "../renderables/static_sprite.h"

namespace GryEngine {

	namespace Graphics {

		// -- really simple renderer --
		// one draw call per sprite rendered
		class SimpleRenderer2D : public Renderer2D
		{
		private:
			// -- the double ended queue that stores renderables --
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			// -- used to submit renderables to the queue --
			void Submit(const Renderable2D* renderable) override;

			//-- used to iterate through the queue, draw renderables, and remove from queue --
			void Flush() override;
		};

	}
}