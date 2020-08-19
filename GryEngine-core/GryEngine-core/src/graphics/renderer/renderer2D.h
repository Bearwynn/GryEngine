#pragma once

#include "GL/glew.h"
#include "../../maths/maths.h"
#include "../renderables/Renderable2D.h"

namespace GryEngine {

	namespace Graphics {

		class Renderer2D
		{
		public:
			//-- pure virtual methods
			//-- this class cannot be instantiated
			//-- when extended, these will be forced to be implemented
			virtual void Submit(const Renderable2D* renderable)	= 0;
			virtual void Flush()								= 0;

		};

	}
}