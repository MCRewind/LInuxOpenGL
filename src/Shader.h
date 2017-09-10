#ifndef SHADER
#define SHADER

class Shader
{
public:
	GLuint vertexShader, fragmentShader, shaderProgram;
	Shader(const char* vertPath, const char* fragPath);
	void enable();
	void disable();
};

#endif
