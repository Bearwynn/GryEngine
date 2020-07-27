#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main()
{
	using namespace GryEngine;
	using namespace Graphics;
	using namespace Maths;

	Window window("GryEngine", 640, 480);	//create a new window
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);	//define the default colour for GL window

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Vector2 vectorOne(1.0f, 2.0f);
	Vector2 vectorTwo(5.0f, 2.0f);

	Vector3 vec31(1.0f, 1.0f, 1.0f);
	Vector3 vec32(2.0f, 2.0f, 2.0f);

	while (!window.Closed())
	{
		window.Clear();

		bool drawSquare = true;
		bool debugMouse = false;
		bool debugInput = false;

		std::cout << vectorOne << std::endl;
		std::cout << vectorTwo << std::endl;
		vectorOne.add(vectorTwo);
		std::cout << vectorOne << std::endl;
		std::cout << vectorTwo << std::endl;

		std::cout << vec31 << std::endl;
		std::cout << vec32 << std::endl;
		vectorOne.add(vectorTwo);
		std::cout << vectorOne << std::endl;
		std::cout << vectorTwo << std::endl;

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

		if (drawSquare)
		{
			// -- draw a square --
			glBegin(GL_QUADS);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(-0.5f,  0.5f);
			glVertex2f( 0.5f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
			glEnd();
		}

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

		window.Update();
	}

	return 0;
}