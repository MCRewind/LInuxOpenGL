#include "GamePanel.h"

#include <iostream>

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	state = 0;
	this->window = window;
	this->camera = camera;
	map = new Map(window, camera, 1006, 8);
}

void GamePanel::update() {

	if (window->isKeyPressed(GLFW_KEY_LEFT_CONTROL))
		if (window->isKeyPressed(GLFW_KEY_O))
			map->importCanvas();

	std::cout << "x: " << window->getMouseCX(camera) / 16 << ", y: " << window->getMouseCY(camera) / 16 << std::endl;

	map->update();
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
}

void GamePanel::render() {
	map->render();
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	delete map;
}