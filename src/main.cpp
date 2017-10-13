#include <iostream>

#include "Window.h"
#include "Camera.h"
#include "Panel.h"

#include "GamePanel.h"

void update();
void render();
void checkState();
void init();

bool slow = false;
bool framesLock = false;
bool slowLock = false;

int framesLeft = 1;
int state;

const uint16 TARGET_FPS = 60;

uint16 fps;
double deltaTime;

Window * window;
Camera * camera;
Panel * panels[1];

int main(int32 argc, char *argv[]) {
	double pastTime = glfwGetTime();
	double curTime, spf = (double)1 / (double)TARGET_FPS;
	uint16 frames = 0;
	double pastSec = pastTime;
	init();
	while (!window->shouldClose()) {
		curTime = glfwGetTime();
		if (curTime - pastTime > spf) {
			deltaTime = curTime - pastTime;
			update();
			render();
			pastTime = curTime;
			++frames;
		}
		if (curTime - pastSec > 1) {
			fps = frames;
			frames = 0;
			++pastSec;
		}
	}
	for (Panel * panel : panels)
		delete panel;
	delete panels;
	delete camera;
	delete window;
	Window::terminate();
	return 0;
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
	panels[state]->update();
	/*if (framesLeft > 0)
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
	}*/
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
