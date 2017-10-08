
#include "GamePanel.h"
#include "Window.h"
#include "Camera.h"
#include "Panel.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

void update(double deltaTime);
void render();
void checkState();
void init();
int state;
Panel* panels[1];
Window* window;
Camera* camera;
bool slow = false, framesLock = false, slowLock = false;
int framesLeft = 1;

int main()
{
	static double limitFPS = 1.0 / 60.0;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	init();

	// - While window is alive
	while (!window->shouldClose()) {
		// - Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		// - Only update at 60 frames / s
		while (deltaTime >= 1.0) {
			update(deltaTime);   // - Update function
			updates++;
			deltaTime--;
		}
		// - Render at maximum possible frames
		render(); // - Render function
		frames++;

		// - Reset after one second
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}	
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

void update(double deltaTime)
{
	checkState();
	window->update();
	if (framesLeft > 0)
	{
		panels[state]->update(deltaTime);
		framesLeft--;
	}
	if (!slow)
	{
		framesLeft++;
	}
	if (window->isKeyPressed(GLFW_KEY_ESCAPE))
		window->close();
	if (window->isKeyPressed(GLFW_KEY_P))
	{
		if (slowLock == false)
		{
			slow = !slow;
			slowLock = true;
		}
	}
	else
	{
		slowLock = false;
	}

	if (window->isKeyPressed(GLFW_KEY_EQUAL) && slow)
	{
		if (framesLock == false)
		{
			framesLeft++;
			framesLock = true;
		}
	}
	else
	{
		framesLock = false;
	}
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
