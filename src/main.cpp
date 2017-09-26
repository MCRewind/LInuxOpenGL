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
#include "GamePanel.h"


#include <iostream>

#include <stdio.h>

private:
	void update();
	void render();
	void checkState();
	void init();
	int state;
	Panel* panels[]; 

glm::mat4 fullTransform()
{
	glm::mat4 temp;
	temp = glm::translate(temp, glm::vec3(0, 0, 0));
	temp = glm::rotate<float>(temp, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::scale(temp, glm::vec3(1, 1, 1));
	return temp;
}

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
	delete vao;
	delete texture;
	delete camera;
}

void init()
{
	Window*	window = new Window(520, 520, "test", true, true); 
        Camera* camera = new Camera(520, 520);
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
	window->bind();
        window->swap();
}

void checkState()
{
	int state = panels[this->state]->getState();
	if (this->state != state)
	{
		switch(state)
		{
			default:
				panels[state].setActive();
		}
		this->state = state;
	}
}
