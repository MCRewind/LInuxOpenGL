#include "GamePanel.h"

GamePanel::GamePanel(Window * window, Camera * camera) : Panel(window, camera) {
	this->window = window;
	this->camera = camera;
	map = new Map(window, camera, 32, 16);
}

void GamePanel::update() {
	map->update();
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