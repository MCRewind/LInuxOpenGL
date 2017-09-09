#include <GLFW/glfw3.h>

#include "Window.h"
#include "Vao.h"

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
	Vao * vao = new Vao(vertices, 4, indices, 6);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while(!window->shouldClose())
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
		vao->render();
		window->swap();
		if (window->isKeyPressed(GLFW_KEY_ESCAPE))
			window->close();
	}
	delete window;
	delete vao;
}
