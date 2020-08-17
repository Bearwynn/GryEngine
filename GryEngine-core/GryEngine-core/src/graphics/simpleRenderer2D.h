#pragma once

#include <deque>
#include "renderer2D.h"

namespace GryEngine {

	namespace Graphics {

		class SimpleRenderer2D : public Renderer2D
		{
		private:
			// -- the double ended queue that stores renderables --
			std::deque<const Renderable2D*> m_RenderQueue;
		public:
			// -- used to submit renderables to the queue --
			void Submit(const Renderable2D* renderable) override;

			//-- used to iterate through the queue, draw renderables, and remove from queue --
			void Flush() override;
		};

	}
}