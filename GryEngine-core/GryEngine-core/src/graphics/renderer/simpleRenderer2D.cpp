#pragma once
#include "simpleRenderer2D.h"

namespace GryEngine {

	namespace Graphics {

		// -- used to submit renderables to the queue --
		void SimpleRenderer2D::Submit(const Renderable2D* renderable)
		{
			m_RenderQueue.push_back((StaticSprite*)renderable);
		}

		//-- used to iterate through the queue, draw renderables, and remove from queue --
		void SimpleRenderer2D::Flush()
		{
			// -- Go through the render queue, and draw renderables --
			while (!m_RenderQueue.empty())
			{
				const StaticSprite* sprite = m_RenderQueue.front(); //get the renderable at the front of the queue
				sprite->GetVertexArray()->Bind();					//bind the vertex array object of the renderable
				sprite->GetIndexBuffer()->Bind();					//bind the index buffer object of the renderable

				Maths::Mat4x4 position = Maths::Mat4x4::translation(sprite->GetPosition());						//generate a new translation matrix based on renderable position
				sprite->GetShader().SetUniformMat4x4("model_matrix", position);									//use the model matrix to position the renderable to the Position
				glDrawElements(GL_TRIANGLES, sprite->GetIndexBuffer()->GetCount(), GL_UNSIGNED_SHORT, nullptr);	//draw the renderable using triangles

				sprite->GetIndexBuffer()->Unbind();					//unbind the index buffer object of the renderable
				sprite->GetVertexArray()->Unbind();					//unbind the vertex array object of the renderable

				//-- remove from render queue --
				m_RenderQueue.pop_front();
			}
		}

	}
}