#include "Shader2c.h"

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
