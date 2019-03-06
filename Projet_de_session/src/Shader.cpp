#include "Shader.h"
#include "ofMain.h"
#include <iostream>

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); // (position in the pipeline)
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*) alloca(length * sizeof(char)); // malloc sur stack
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader compilation failed: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::cout << vertexShader << std::endl << fragmentShader << std::endl;
	unsigned int programID = glCreateProgram();
	unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return programID;
}

Shader::Shader()
{
	
}


Shader::~Shader()
{
}
