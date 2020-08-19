#pragma once
#include "renderable2D.h"

namespace GryEngine {

	namespace Graphics {

		class  Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, Maths::Vector4& colour);

		};

	}
}
