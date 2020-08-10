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

	bool debugMouse			= true;
	bool debugInput			= true;
	bool debugUseShader		= true;
	bool debugTestBuffer	= false;

	Window window("GryEngine", 640, 480);	//create a new window
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//define the default colour for GL window


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
		shader.SetUniform4float("fragColour", Vector4(1.0f, 0.3f, 1.0f, 1.0f));

		while (!window.Closed())
		{
			window.Clear();

			double x, y;
			window.getMousePosition(x, y);
			shader.SetUniform2float("light_position", Vector2((float)(x * 16.0f / 640.0f), (float)(9.0f - y * 9.0f / 480.0f)));
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

		VertexArray vao;
		Buffer* vbo = new Buffer(vertices, 4 * 3, 3);
		IndexBuffer ibo(indices, 6);

		vao.AddBuffer(vbo, 0);

		while (!window.Closed())
		{
			window.Clear();

			if (debugMouse)
			{
				double x, y;
				window.getMousePosition(x, y);
				std::cout << "Mouse Position: " << x << ", " << y << std::endl;
			}

			if (debugInput)
			{
				if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::cout << "LEFT MOUSE PRESSED!" << std::endl;
				}

				if (window.isMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
				{
					std::cout << "RIGHT MOUSE PRESSED!" << std::endl;
				}
			}

			if (debugTestBuffer)
			{
				vao.Bind();
				ibo.Bind();

				glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

				ibo.Unbind();
				vao.Unbind();
			}

			window.Update();
		}
	}

	return 0;
}