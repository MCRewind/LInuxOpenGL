#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include "Vao.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"
#include "Rect.h"
#include "TexRect.h"
#include "Panel.h"
#include "GamePanel.h"

Texture* tex0, *tex1;
Texture* getTex(int id);

int map[5][5] =
{
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 1, 0, 1, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 0, 0
};

GamePanel::GamePanel(Window* window, Camera* camera) : Panel(window, camera)
{
	state = 0;
	tex0 = new Texture("res/textures/test.png");
	tex1 = new Texture("res/textures/cmbt.png");
	texture = new TexRect(camera, "res/textures/test.png", 100, 100, 0, 16, 16);
}

Texture* getTex(int id)
{
	switch (id)
	{
	case 0:
		return tex0;
	case 1:
		return tex1;
	default:
		return tex0;
	}
}

void GamePanel::update()
{
	/*************CAMERA MOVEMENT***********/
	if (window->isKeyPressed(GLFW_KEY_LEFT))
		camera->translate(glm::vec3(-3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_RIGHT))
		camera->translate(glm::vec3(3, 0, 0));
	if (window->isKeyPressed(GLFW_KEY_UP))
		camera->translate(glm::vec3(0, -3, 0));
	if (window->isKeyPressed(GLFW_KEY_DOWN))
		camera->translate(glm::vec3(0, 3, 0));
	if (window->isKeyPressed(GLFW_KEY_N))
		texture->zoomi();
	if (window->isKeyPressed(GLFW_KEY_M))
		texture->zoomo();
}

void GamePanel::render()
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			texture->setPos(i * 16, j * 16);
			texture->setTexture(getTex(map[i][j]));
			texture->render();
		}
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	delete texture;
}
