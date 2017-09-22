#ifndef SHADER
#define SHADER

class Shader
{
public:
	class Shader2c : Shader;
	class Shader2t : Shader;
	GLuint vertexShader, fragmentShader, shaderProgram;
	Shader(const char* vertPath, const char* fragPath);
	GLint getUniformLoc(const char* name);
	void setProjection(glm::mat4);
	void setView(glm::mat4);
	void setModel(glm::mat4);
	void enable();
	void disable();
private:
	int projLoc, viewLoc, modelLoc;
};

#endif
