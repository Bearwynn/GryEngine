#pragma once
#include "../../maths/maths.h"

namespace GryEngine {

	namespace Graphics {

		class VertexData
		{
		public:
			Maths::Vector3 vertex;
			Maths::Vector4 colour;
		};

		class Renderable2D
		{
		protected:
			// -- Vector Data --
			Maths::Vector3 m_Position;
			Maths::Vector2 m_Size;
			Maths::Vector4 m_Colour;

		public:
			Renderable2D(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 colour)
				: m_Position(position), m_Size(size), m_Colour(colour) {};
			~Renderable2D() {};

			inline const Maths::Vector3& GetPosition()	const { return m_Position; };
			inline const Maths::Vector2& GetSize()		const { return m_Size; };
			inline const Maths::Vector4& GetColour()	const { return m_Colour; };
		};

	}
}