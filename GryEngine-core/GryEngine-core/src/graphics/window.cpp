#include "window.h"

namespace GryEngine {

	namespace Graphics {
		// -- forward declaration non class functions --
		void window_Resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_callback(GLFWwindow* window, int button, int action, int mods);
		void mousePosition_callback(GLFWwindow* window, double xpos, double ypos);


		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			// -- check if Init() succeeded --
			if (!Init())
				glfwTerminate();

			// -- setup input --
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::Init()
		{
			// -- check initialization --
			if (!glfwInit())
			{
				std::cout << "GLFW window failed to initialize!" << std::endl;
				return false;
			}
			else
			{
				std::cout << "GLFW Init Success!" << std::endl;
			}

			// -- create GLFW window ---
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			// -- check GLFW window creation --
			if (!m_Window)
			{
				glfwTerminate();
				std::cout << "GLFW window creation failed!" << std::endl;
				return false;
			}
			else
			{
				std::cout << "GLFW window creation success!" << std::endl;
			}

			// -- GLFW window complete --
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this); //set this window as the user pointer
			glfwSetWindowSizeCallback(m_Window, window_Resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_callback);
			glfwSetCursorPosCallback(m_Window, mousePosition_callback);
			
			// -- GLEW initialization --
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW failed to initialize!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;
		}
		 
		void Window::Update()
		{
			// -- error check --
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;


			glfwPollEvents();			//polling for events (eg input callbacks)
			glfwSwapBuffers(m_Window);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		// -- input checking --
		bool Window::IsKeyPressed(unsigned int keycode) const
		{
			//TODO: log this
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool Window::IsMousePressed(unsigned int button) const
		{
			//TODO: log this
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		void Window::GetMousePosition(double& x, double& y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		// -- non class functions --
		void window_Resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);	//getting a pointer to a window
			win->m_Keys[key] = action != GLFW_RELEASE;					//if a key is not released, set it to true
		}

		void mouse_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);	//getting a pointer to a window
			win->m_MouseButtons[button] = action != GLFW_RELEASE;		//if a mouse key is not released, set it to true
		}

		void mousePosition_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);	//getting a pointer to a window
			win->m_MouseX = xpos;
			win->m_MouseY = ypos;
		}
	}
}