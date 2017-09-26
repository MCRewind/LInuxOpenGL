#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include "Shader.h"

	Shader2c::Shader2c()
	{
		Shader::("/res/shader/s2c/vert.glsl", "/res/shaders/s2c/frag.glsl");
	}

	void Shader2c::getUniformLocs(const char* name)
	{
		Shader::getUniformLocs(name);
		colorLoc = glGetUniformLocation(program, "iColor");
	}

	void Shader2c::setColor(float r, float g, float b, float a)
	{
		glUniform4f(colorLoc, r, g, b, a);
	}

	Shader2c::~Shader2c()
	{
	
	}

	Shader2t::Shader2t()
	{
		Shader::("/res/shader/s2t/vert.glsl", "/res/shaders/s2t/frag.glsl");
	}

	Shader2t::~Shader2t()
	{
	
	}

std::string readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Shader::Shader(const char* vertPath, const char* fragPath)
{
	SHADER2C = new Shader2c();
	shaderProgram = glCreateProgram();
	//Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertSource = readFile(vertPath);
	const GLchar *vc_str = vertSource.c_str();
	glShaderSource(vertexShader, 1, &vc_str, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cerr << "Failed to compile shader : " << vertPath << "!" << buffer;
		//exit(-1);
	}
	glAttachShader(shaderProgram, vertexShader);

	//Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragSource = readFile(fragPath);
	const GLchar *fc_str = fragSource.c_str();
	glShaderSource(fragmentShader, 1, &fc_str, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cerr << "Failed to compile shader : " << fragPath << "!" << buffer;
		//exit(-1);
	}
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	projLoc = getUniformLoc("proj");
	viewLoc = getUniformLoc("view");
	modelLoc = getUniformLoc("model");
}

GLint Shader::getUniformLoc(const char* name)
{
	return glGetUniformLocation(shaderProgram, name);
}

void Shader::setProjection(glm::mat4 projection)
{
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::setView(glm::mat4 view)
{
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Shader::setModel(glm::mat4 model)
{
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::enable()
{
	glUseProgram(shaderProgram);
}

void Shader::disable()
{
	glUseProgram(0);
}
