#include "shaderProgram.h"

Shader::Shader (GLenum shaderType, const GLchar * source)
{
	this->id = glCreateShader(shaderType);
	glShaderSource(this->id, 1, &source, nullptr);
	glCompileShader(this->id);
	GLint success;
	glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog [512];
		glGetShaderInfoLog(this->id, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failure:\n"
			<< infoLog << std::endl;
		glDeleteShader(this->id);
		this->id = 0;
	}
}

Shader::~Shader ( void )
{
	glDeleteShader(this->id);
}

GLuint Shader::getId( void )
{
	return this->id;
}

ShaderProgram::ShaderProgram (Shader ** shaders, GLuint shaderCount)
{
	this->id = glCreateProgram();
	for (unsigned int i = 0; i < shaderCount; i++)
		glAttachShader(this->id, shaders[i]->getId());
	glLinkProgram(this->id);
	GLint success;
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog [512];
		glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failure:\n"
			<< infoLog << std::endl;
		glDeleteProgram(this->id);
		this->id = 0;
	}
}

ShaderProgram::~ShaderProgram ( void )
{
	glDeleteProgram(this->id);
}

GLuint ShaderProgram::getId( void )
{
	return this->id;
}
