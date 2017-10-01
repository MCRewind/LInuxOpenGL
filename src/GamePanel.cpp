#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Rect.h"
#include "Player.h"
#include "GamePanel.h"

#include <iostream>

Texture* tex0, *tex1;
Texture* getTex(int id);
Player* player;

char *states[] =
{
	"Stand",
	"Walk",
	"Jump",
	"GrabLedge"
};

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
	player = new Player(camera);
	texture = new TexRect(camera, "res/textures/test.png", 0, 0, 0, 16, 16);
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

void GamePanel::update(double deltaTime)
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
		camera->zoomi();
	if (window->isKeyPressed(GLFW_KEY_M))
		camera->zoomo();

	if (window->isKeyPressed(GLFW_KEY_W))
		player->inputs[(int)player->KeyJump] = true;
	else
		player->inputs[(int)player->KeyJump] = false;
	if (window->isKeyPressed(GLFW_KEY_A))
		player->inputs[(int)player->GoLeft] = true;
	else
		player->inputs[(int)player->GoLeft] = false;
	if (window->isKeyPressed(GLFW_KEY_S))
		player->inputs[(int)player->GoDown] = true;
	else
		player->inputs[(int)player->GoDown] = false;
	if (window->isKeyPressed(GLFW_KEY_D))
		player->inputs[(int)player->GoRight] = true;
	else
		player->inputs[(int)player->GoRight] = false;

	player->update(deltaTime);
	std::cout << player->spd.x << ", " << player->spd.y << ", " << player->pos.x << ", " << player->pos.y << ", " << states[player->currentState] << std::endl;
	//camera->setPos(glm::vec3(player->pos.x, player->pos.y, 0));
}

void GamePanel::render()
{
	player->render();
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
