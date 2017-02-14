#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <iostream>

#include <GL/glew.h>


class Shader
{
	GLuint id;
	GLenum shaderType;
	
	public:
		Shader(GLenum shaderType, const GLchar * source);
		~Shader( void );
		GLuint getId( void );
};

class ShaderProgram
{
	GLuint id;
	
	public:
		ShaderProgram(Shader ** shaders, GLuint shadersCount);
		~ShaderProgram( void );
		GLuint getId( void );
};

#endif  // __SHADERPROGRAM_H__
