#include <GLFW/glfw3.h>

#include "Window.h"
#include "Vao.h"
#include "Shader.h"
#include "Texture.h"

#include <stdio.h>

int main()
{
	Window* window = new Window(520, 520, "test", true, true);

	float vertices[] = {
		-0.5,  0.5, 0,
		-0.5, -0.5, 0,
		0.5, -0.5, 0,
		0.5,  0.5, 0
	};
	int indices[] = {
		0, 1, 3,
		3, 1, 2
	};
	float texCoords[] = {
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};
	Vao* vao = new Vao(vertices, 4, indices, 6);

	vao->addAttrib(texCoords, 4, 2);

	Shader* shader = new Shader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");

	Texture* texture = new Texture("res/textures/test.png");

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (!window->shouldClose())
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		window->update();
		window->clear();
		shader->enable();
		texture->bind();
		vao->render();
		texture->unbind();
		shader->disable();
		window->swap();
		if (window->isKeyPressed(GLFW_KEY_ESCAPE))
			window->close();
	}
	delete window;
	delete vao;
	delete texture;
}
