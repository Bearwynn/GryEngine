#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/file_utils.h"
#include "src/graphics/shader/shader.h"

int main()
{
	using namespace GryEngine;
	using namespace Graphics;
	using namespace Maths;

	bool drawSquare		= false;
	bool debugMouse		= false;
	bool debugInput		= false;
	bool debugVector	= false;
	bool debugMatrix	= false;
	bool debugFileRead	= false;
	bool debugUseShader = true;

	Window window("GryEngine", 640, 480);	//create a new window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//define the default colour for GL window

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

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		GLuint vbo;
		glGenBuffers(1, &vbo);														//generate an openGL buffer (like an array)
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//populate the buffer with data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		shader.Enable();
	}

	if (debugVector)
	{
		Vector2 vectorOne(1.0f, 2.0f);
		Vector2 vectorTwo(5.0f, 2.0f);

		Vector3 vec31(1.0f, 1.0f, 1.0f);
		Vector3 vec32(2.0f, 2.0f, 2.0f);

		std::cout << vectorOne << std::endl;
		std::cout << vectorTwo << std::endl;
		vectorOne.add(vectorTwo);
		std::cout << vectorOne << std::endl;
		std::cout << vectorTwo << std::endl;

		std::cout << vec31 << std::endl;
		std::cout << vec32 << std::endl;
		vec31.add(vec32);
		std::cout << vec31 << std::endl;
		std::cout << vec32 << std::endl;
	}

	if (debugMatrix)
	{
		Mat4x4 position = Mat4x4::translation(Vector3(2.0f, 3.0f, 4.0f));
		position *= Mat4x4::identity();

		Vector4 column = position.column[3];
		std::cout << column << std::endl;
		std::cout << "Start Address Value of: " << position.elements[12] << " | " << &position.elements[12] << std::endl;
		std::cout << "Start Address Value of: " << column << " | " << &position.column[3] << std::endl;
	}
	
	if (debugFileRead)
	{
		std::cout << "TESTING FILE READ" << std::endl;
		std::string file = FileUtils::read_file("main.cpp");
		std::cout << file << std::endl;
		system("PAUSE");
		return 0;
	}

	while (!window.Closed())
	{
		window.Clear();

		//if (debugMouse)
		//{
		//	double x, y;
		//	window.getMousePosition(x, y);
		//	std::cout << "Mouse Position: " << x << ", " << y << std::endl;
		//}

		//if (debugInput)
		//{
		//	if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		//	{
		//		std::cout << "LEFT MOUSE PRESSED!" << std::endl;
		//	}

		//	if (window.isMousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		//	{
		//		std::cout << "RIGHT MOUSE PRESSED!" << std::endl;
		//	}
		//}

		//if (drawSquare)
		//{
		//	// -- draw a square --
		//	glBegin(GL_QUADS);
		//	glVertex2f(-0.5f, -0.5f);
		//	glVertex2f(-0.5f,  0.5f);
		//	glVertex2f( 0.5f,  0.5f);
		//	glVertex2f( 0.5f, -0.5f);
		//	glEnd();
		//}

		if (debugUseShader)
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		window.Update();
	}

	return 0;
}