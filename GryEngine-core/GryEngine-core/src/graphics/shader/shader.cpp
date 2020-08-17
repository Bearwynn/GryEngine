#include "shader.h"
#include <vector>
#include <iostream>

namespace GryEngine {

	namespace Graphics {

		Shader::Shader(const char* vertPath, const char* fragPath) 
		{
			m_VertPath = vertPath;	//store the file path for vert shader
			m_FragPath = fragPath;	//store the file path for frag shader

			m_ShaderID = Load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		GLuint Shader::Load()
		{
			// setup the openGL Program
			GLuint glProgram = glCreateProgram();

			GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtils::read_file(m_VertPath);
			std::string fragSourceString = FileUtils::read_file(m_FragPath);
			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			#pragma region VERTEX SHADER
			// -- VERTEX SHADER --
			//set the openGL shader source, and compile
			glShaderSource(vertShader, 1, &vertSource, NULL);
			glCompileShader(vertShader);

			//check if vertShader compiled successfully
			GLint vertResult;
			glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertResult);
			if (vertResult == GL_FALSE)
			{
				//get the openGL error
				GLint length;
				glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertShader, length, &length, &error[0]);

				//output the openGL error
				std::cout << "Failed to compile vertex shader!: " << std::endl << &error[0] << std::endl;

				//delete the openGL shader
				glDeleteShader(vertShader);
				return 0;
			}
			else
			{
				std::cout << "Vert shader compiled successfully!" << std::endl;
			}
			#pragma endregion

			#pragma region FRAGMENT SHADER
			// -- FRAGMENT SHADER --
			
			//set the openGL shader source, and compile
			glShaderSource(fragShader, 1, &fragSource, NULL);
			glCompileShader(fragShader);

			//check if fragShader compiled successfully
			GLint fragResult;
			glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragResult);
			if (fragResult == GL_FALSE)
			{
				//get the openGL error
				GLint length;
				glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragShader, length, &length, &error[0]);

				//output the openGL error
				std::cout << "Failed to compile fragment shader!: " << std::endl << &error[0] << std::endl;

				//delete the openGL shader
				glDeleteShader(fragShader);
				return 0;
			}
			else
			{
				std::cout << "Frag shader compiled successfully!" << std::endl;
			}
			#pragma endregion

			// attach the shaders to the openGL program
			glAttachShader(glProgram, vertShader);
			glAttachShader(glProgram, fragShader);

			// link the openGl program to openGL
			glLinkProgram(glProgram);
			glValidateProgram(glProgram);

			// delete the shaders now we are done with them
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return 1;
		}

		GLint Shader::GetUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::SetUniform1float(const GLchar* name, float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::SetUniform1int(const GLchar* name, int value)
		{
			glUniform1i(GetUniformLocation(name), value);
		}

		void Shader::SetUniform2float(const GLchar* name, const Maths::Vector2& vector)
		{
			glUniform2f(GetUniformLocation(name), vector.x, vector.y);
		}

		void Shader::SetUniform3float(const GLchar* name, const Maths::Vector3& vector)
		{
			glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::SetUniform4float(const GLchar* name, const Maths::Vector4& vector)
		{
			glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::SetUniformMat4x4(const GLchar* name, const Maths::Mat4x4& matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}


		void Shader::Enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::Disable() const
		{
			glUseProgram(0);
		}
	}
}