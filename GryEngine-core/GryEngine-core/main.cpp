#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/file_utils.h"

#include "src/graphics/shader/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexBuffer.h"
#include "src/graphics/buffers/vertexArray.h"

int main()
{
	using namespace GryEngine;
	using namespace Graphics;
	using namespace Maths;

	bool debugMouse			= false;
	bool debugInput			= false;
	bool debugUseShader		= false;
	bool debugTestBuffer	= true;

	int horizontalWindowSize	= 640;
	int verticalWindowSize		= 480;

	Window window("GryEngine", horizontalWindowSize, verticalWindowSize);	//create a new window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);									//define the default colour for GL window


	if (debugUseShader)
	{
		/*GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};*/

		GLfloat vertices[] =
		{
			0, 0, 0,
			8, 0, 0,
			0, 3, 0,
			0, 3, 0,
			8, 3, 0,
			8, 0, 0
		};

		GLuint vbo;
		glGenBuffers(1, &vbo);														//generate an openGL buffer (like an array)
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//populate the buffer with data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		Mat4x4 ortho = Mat4x4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		shader.Enable();
		shader.SetUniformMat4x4("projection_matrix", ortho);
		shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(4.0f, 3.0f, 0)));

		shader.SetUniform2float("light_position", Vector2(8.0f, 4.5f));
		shader.SetUniform1float("light_intensity", 2.0f);
		shader.SetUniform4float("frag_colour", Vector4(1.0f, 0.3f, 1.0f, 1.0f));

		while (!window.Closed())
		{
			if (debugMouse)
			{
				double x, y;
				window.GetMousePosition(x, y);
				std::cout << "Mouse Position: " << x << ", " << y << std::endl;
			}

			if (debugInput)
			{
				if (window.IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::cout << "LEFT MOUSE PRESSED!" << std::endl;
				}

				if (window.IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
				{
					std::cout << "RIGHT MOUSE PRESSED!" << std::endl;
				}
			}


			window.Clear();

			double x, y;
			window.GetMousePosition(x, y);
			shader.SetUniform2float("light_position", Vector2((float)(x * 16.0f / (float)horizontalWindowSize), (float)(9.0f - y * 9.0f / (float)verticalWindowSize)));
			glDrawArrays(GL_TRIANGLES, 0, 6);

			window.Update();
		}
	}

	if (debugTestBuffer)
	{
		GLfloat vertices[] = {
			   0, 0, 0,
			   0, 3, 0,
			   8, 3, 0,
			   8, 0, 0
		};

		GLushort indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		VertexArray vao;								//new vertex array declared
		Buffer* vbo = new Buffer(vertices, 4 * 3, 3);	//new vertex buffer using vertices, with 4*3 elements, consisting of 3 elements per component
		IndexBuffer ibo(indices, 6);					//new indexBuffer using the indices generated, with 6 elements

		vao.AddBuffer(vbo, 0);							//add the vertex buffer object to the vertex array buffer

		// -- setup orthographic matrix
		Mat4x4 ortho = Mat4x4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		// -- setup shader --
		Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		shader.Enable();
		shader.SetUniformMat4x4("projection_matrix", ortho);
		shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(4, 3, 0)));

		// -- setup light --
		Vector2 position	= Vector2(4.0f, 1.5f);
		float intensity		= 1.0f;
		Vector4 colour		= Vector4(0.2f, 0.3f, 0.8f, 1.0f);
		shader.SetUniform2float("light_position", position);
		shader.SetUniform1float("light_intensity", intensity);
		shader.SetUniform4float("frag_colour", colour);

		while (!window.Closed())
		{
			window.Clear();

			if (debugMouse)
			{
				double x, y;
				window.GetMousePosition(x, y);
				std::cout << "Mouse Position: " << x << ", " << y << std::endl;
			}

			if (debugInput)
			{
				if (window.IsMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::cout << "LEFT MOUSE PRESSED!" << std::endl;
				}

				if (window.IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
				{
					std::cout << "RIGHT MOUSE PRESSED!" << std::endl;
				}
			}

			if (debugTestBuffer)
			{
				// -- make light follow mouse --
				double x;
				double y;
				window.GetMousePosition(x, y);
				shader.SetUniform2float("light_position", Vector2((float)(x * 16.0f / (float)horizontalWindowSize), (float)(9.0f - y * 9.0f / (float)verticalWindowSize)));

				// -- draw object to the screen --
				vao.Bind();
				ibo.Bind();
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				ibo.Unbind();
				vao.Unbind();
			}

			window.Update();
		}

		//cleanup memory
		delete vbo;
	}

	return 0;
}