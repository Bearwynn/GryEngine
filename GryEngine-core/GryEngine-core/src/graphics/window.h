#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GryEngine {

	namespace Graphics {

#define MAX_KEYS			1024
#define MAX_MOUSE_BUTTONS	32

		class Window 
		{
		private:
			friend struct GLFWwindow;
			const char *m_Title;
			int m_Width;
			int m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;

			//-- user input --
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_MOUSE_BUTTONS];
			double m_MouseX;
			double m_MouseY;
		public:
			Window(const char *title, int width, int height);
			~Window();
			void Clear() const;
			void Update();
			bool Closed() const;

			//function to be called whenever error checking is required
			void CheckError(const char* errorTag);

			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }

			bool IsKeyPressed(unsigned int keycode) const;
			bool IsMousePressed(unsigned int button) const;
			void GetMousePosition(double& x, double& y) const; //eventually will return a Vector2D
		private:
			bool Init();
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_callback(GLFWwindow* window, int button, int action, int mods);
			friend void mousePosition_callback(GLFWwindow* window, double xpos, double ypos);
		};



	}
}