#include <iostream>

#include "Window.h"
#include "Camera.h"
#include "Panel.h"

#include "GamePanel.h"

void update();
void render();
void checkState();
void init();

Window* window;
Camera* camera;
Panel* panels[1];

bool slow = false, framesLock = false, slowLock = false;
int framesLeft = 1;
int state;
double deltaTime = 0;

int main()
{
	static double limitFPS = 1.0 / 60.0;

	double lastTime = glfwGetTime(), timer = lastTime;
	double nowTime = 0;
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
			update();   // - Update function
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
	for(Panel * panel : panels)
		delete panel;
	delete[] panels;
	delete window;
	delete camera;
}

void init()
{
	window = new Window(0, 0, "test", true, true);
	camera = new Camera(window->getWidth(), window->getHeight());
	panels[0] = new GamePanel(window, camera);
	state = 0;
}

void update( )
{
	checkState();
	window->poll();
	if (framesLeft > 0)
	{
		panels[state]->update();
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
