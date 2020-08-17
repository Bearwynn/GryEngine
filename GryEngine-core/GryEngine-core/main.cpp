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
			Vector2 lightPosition = Vector2((float)(x * 16.0f / (float)horizontalWindowSize), (float)(9.0f - y * 9.0f / (float)verticalWindowSize));
			shader.SetUniform2float("light_position", lightPosition);
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

		GLfloat red[] = 
		{
			1, 0, 0, 1,
			1, 0, 0, 1,
			1, 0, 0, 1,
			1, 0, 0, 1
		};

		GLfloat green[] =
		{
			0, 1, 0, 1,
			0, 1, 0, 1,
			0, 1, 0, 1,
			0, 1, 0, 1
		};

		GLfloat blue[] =
		{
			0, 0, 1, 1,
			0, 0, 1, 1,
			0, 0, 1, 1,
			0, 0, 1, 1
		};


		GLfloat yellow[] =
		{
			1, 1, 0, 1,
			1, 1, 0, 1,
			1, 1, 0, 1,
			1, 1, 0, 1,
		};

		GLfloat white[] =
		{
			1, 1, 1, 1,
			1, 1, 1, 1,
			1, 1, 1, 1,
			1, 1, 1, 1,
		};

		GLfloat Rainbow[] =
		{
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			1, 1, 0, 1,
		};

		VertexArray sprite1, sprite2, sprite3, sprite4, sprite5;	//new vertex array declared
		IndexBuffer ibo(indices, 6);								//new indexBuffer using the indices generated, with 6 elements

		sprite1.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);		//add the vertex buffer object to a new vertex array buffer 0
		sprite1.AddBuffer(new Buffer(red, 4 * 4, 4), 1);			//add the coloursA array to a new colours buffer 1
		sprite2.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);		//add the vertex buffer object to a new vertex array buffer 0
		sprite2.AddBuffer(new Buffer(green, 4 * 4, 4), 1);			//add the coloursB array to a new colours buffer 1
		sprite3.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);		//add the vertex buffer object to a new vertex array buffer 0
		sprite3.AddBuffer(new Buffer(blue, 4 * 4, 4), 1);			//add the coloursB array to a new colours buffer 1
		sprite4.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);		//add the vertex buffer object to a new vertex array buffer 0
		sprite4.AddBuffer(new Buffer(Rainbow, 4 * 4, 4), 1);		//add the coloursB array to a new colours buffer 1
		sprite5.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);		//add the vertex buffer object to a new vertex array buffer 0
		sprite5.AddBuffer(new Buffer(yellow, 4 * 4, 4), 1);			//add the coloursB array to a new colours buffer 1



		// -- setup orthographic matrix
		Mat4x4 ortho = Mat4x4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		// -- setup shader --
		Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		shader.Enable();
		shader.SetUniformMat4x4("projection_matrix", ortho);
		shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(4, 3, 0)));

		// -- setup light --
		Vector2 position	= Vector2(4.0f, 1.5f);
		Vector4 colour		= Vector4(0.2f, 0.3f, 0.8f, 1.0f);
		shader.SetUniform2float("light_position", position);
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

				// -- DRAW SPRITE 1 (RED) --
				sprite1.Bind();
				ibo.Bind();
				shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(0, 0, 0)));
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				window.CheckError("Sprite1");
				ibo.Unbind();
				sprite1.Unbind();
				
				// -- DRAW SPRITE 2 (GREEN) --
				sprite2.Bind();
				ibo.Bind();
				shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(0, 6, 0)));
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				window.CheckError("Sprite2");
				sprite2.Unbind();
				ibo.Unbind();

				// -- DRAW SPRITE 3 (BLUE) --
				sprite3.Bind();
				ibo.Bind();
				shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(8, 6, 0)));
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				window.CheckError("Sprite3");
				sprite2.Unbind();
				ibo.Unbind();

				// -- DRAW SPRITE 5 (YELLOw) --
				sprite5.Bind();
				ibo.Bind();
				shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(8, 0, 0)));
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				window.CheckError("Sprite5");
				sprite5.Unbind();
				ibo.Unbind();

				// -- DRAW SPRITE 4 (RAiNBOW) --
				sprite4.Bind();
				ibo.Bind();
				shader.SetUniformMat4x4("model_matrix", Mat4x4::translation(Vector3(4, 3, 0)));
				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
				window.CheckError("Sprite4");
				sprite4.Unbind();
				ibo.Unbind();
			}

			window.Update();
		}
	}

	return 0;
}