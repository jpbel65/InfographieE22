#pragma once
#include <string>

class Shader
{
	unsigned int programID;

public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader="");
	static std::string* importShader(const std::string& filePath);

	unsigned int getProgramID() { return programID; };

	Shader();
	Shader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource = "");
	~Shader();
};

