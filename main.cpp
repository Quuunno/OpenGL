#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "resources.h"
#include "shaderProgram.h"

void keyCallback(GLFWwindow * win, GLint key, GLint scn, GLint act,
	GLint mod);

int main (void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	GLFWwindow * window = glfwCreateWindow(640, 480, "Learn OpenGL", 
		nullptr, nullptr);
		
	if (window)
	{
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, keyCallback);
		if (glewInit() == GLEW_OK)
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
			
			Shader * vxs = new Shader(GL_VERTEX_SHADER, 
				readText("shaders/vertex.glsl").c_str());
			Shader * frs = new Shader(GL_FRAGMENT_SHADER,
				readText("shaders/fragment.glsl").c_str());
			Shader * shaders [] {vxs, frs};
			ShaderProgram * spr = new ShaderProgram(shaders, 2);
			
			GLfloat verticles [] {
				-0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f
			};
			
			GLuint VBO; glGenBuffers(1, &VBO);
			GLuint VAO; glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
				
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(verticles),
					verticles, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 
					sizeof(GLfloat), (GLvoid *) 0);
				glEnableVertexAttribArray(0);
				
			glBindVertexArray(0);

			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();
				
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				
				glUseProgram(spr->getId());
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(0);
				
				glfwSwapBuffers(window);
			}
		}
		else
		{
			std::cerr << "Failed to initialize GLEW" << std::endl;
			glfwTerminate();
			return 1;
		};
	}
	else
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	};
}

void keyCallback(GLFWwindow * win, GLint key, GLint scn, GLint act,
	GLint mod)
{
	if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
}
