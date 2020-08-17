#pragma once
#include "simpleRenderer2D.h"

namespace GryEngine {

	namespace Graphics {

		// -- used to submit renderables to the queue --
		void SimpleRenderer2D::Submit(const Renderable2D* renderable)
		{
			m_RenderQueue.push_back(renderable);
		}

		//-- used to iterate through the queue, draw renderables, and remove from queue --
		void SimpleRenderer2D::Flush()
		{
			// -- Go through the render queue, and draw renderables --
			while (!m_RenderQueue.empty())
			{
				const Renderable2D* renderable = m_RenderQueue.front(); //get the renderable at the front of the queue
				renderable->GetVertexArray()->Bind();					//bind the vertex array object of the renderable
				renderable->GetIndexBuffer()->Bind();					//bind the index buffer object of the renderable

				Maths::Mat4x4 position = Maths::Mat4x4::translation(renderable->GetPosition());						//generate a new translation matrix based on renderable position
				renderable->GetShader().SetUniformMat4x4("model_matrix", position);									//use the model matrix to position the renderable to the Position
				glDrawElements(GL_TRIANGLES, renderable->GetIndexBuffer()->GetCount(), GL_UNSIGNED_SHORT, nullptr);	//draw the renderable using triangles

				renderable->GetIndexBuffer()->Unbind();					//unbind the index buffer object of the renderable
				renderable->GetVertexArray()->Unbind();					//unbind the vertex array object of the renderable

				//-- remove from render queue --
				m_RenderQueue.pop_front();
			}
		}

	}
}