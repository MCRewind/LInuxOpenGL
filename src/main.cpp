#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Window.h"
#include "Vao.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Panel.h"
#include "Rect.h"
#include "TexRect.h"
#include "GamePanel.h"

#include <iostream>

#include <stdio.h>

void update();
void render();
void checkState();
void init();
int state;
Panel* panels[1];
Window* window;
Camera* camera;

int main()
{
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	init();

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
		update();
		render();
	}
	delete window;
	delete camera;
}

void init()
{
	window = new Window(1080, 720, "test", true, true);
	camera = new Camera(1080, 720);
	panels[0] = new GamePanel(window, camera);
	state = 0;
}

void update()
{
	checkState();
	window->update();
	panels[state]->update();
	if (window->isKeyPressed(GLFW_KEY_ESCAPE))
		window->close();
}

void render()
{
	window->clear();
	panels[state]->render();
	window->swap();
}

void checkState()
{
	int tempState = panels[state]->getState();
	if (state != tempState)
	{
		switch(tempState)
		{
			default:
				panels[tempState]->setActive();
		}
		state = tempState;
	}
}
