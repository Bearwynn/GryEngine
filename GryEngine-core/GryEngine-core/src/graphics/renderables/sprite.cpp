
#include "sprite.h"


namespace GryEngine {

	namespace Graphics {

		Sprite::Sprite(float x, float y, float width, float height, Maths::Vector4& colour)
			: Renderable2D(Maths::Vector3(x, y, 0), Maths::Vector2(width, height), colour)
		{

		}

	}
}