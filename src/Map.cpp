#include <iostream>
#include <math.h>

#include "Vector4f.h"

#include "Hitbox.h"

#include "Map.h"

Map::Map(Window * window, Camera2d * camera, uint16 width, uint16 height) {
	this->camera = camera;
	this->width = width;
	this->height = height;
	map = new uint16[width * height];
	tiles[0] = new Tile(camera, "res/img/stone.png", false, 0.5, DIMS, DIMS);
	tiles[1] = new Tile(camera, "res/img/cobblestone_mossy.png", true, 0.5, DIMS, DIMS);
	for (uint16 i = 0; i < width; ++i) {
		for (uint16 j = 0; j < height; ++j) {
			if(j == 10 || (i > (height - j) && j < 11 && i % 2 == 0))
				map[i * height + j] = 1;
			else
				map[i * height + j] = 0;
		}
	}
	player = new Player(window, camera, "res/img/samby.png", 0, DIMS * 8, 0, DIMS, DIMS, 12);
}

void Map::update() {
	player->update();
	while (checkCollision());
}

bool Map::checkCollision() {
	Hitbox * playerHit = player->getHitbox();
	Hitbox * closest = 0;
	Hitbox * current = 0;
	Vector3f closestLength;
	int minX = floor(player->getX() / DIMS);
	int maxX = ceil(player->getX() / DIMS);
	int minY = floor(player->getY() / DIMS);
	int maxY = ceil(player->getY() / DIMS);
	if (minX >= 0 && maxX < width && minY >= 0 && maxY < height) {
		for (uint8 i = minX; i <= maxX; ++i) {
			for (uint8 j = minY; j <= maxY; ++j) {
				Tile * curTile = tiles[map[i * height + j]];
				if (curTile->isSolid()) {
					if (!closest) {
						closest = new Hitbox(i * DIMS, j * DIMS, DIMS, DIMS);
						closestLength = closest->getCenter().sum(-playerHit->getCenter());
					}
					else {
						if (current)
							delete current;
						current = new Hitbox(i * DIMS, j * DIMS, DIMS, DIMS);
						Vector3f curLength = current->getCenter().sum(-playerHit->getCenter());
						if (curLength.lengthSquared() < closestLength.lengthSquared()) {
							closestLength = curLength;
							delete closest;
							closest = current;
							current = 0;
						}
					}
				}
			}
		}
	}
	bool ret = false;
	if (closest) {
		if (closest->collides(playerHit)) {
			Vector3f transform = closest->getTransform(playerHit);
			if(transform.y < 0)
				player->landed();
			player->translate(transform);
			player->alignHitbox();
			ret = true;
		}
		if (current)
			delete current;
		delete closest;
	}
	return ret;
}

void Map::render() {
	player->render();
	int minX = fmax(camera->getX() / DIMS, 0);
	int maxX = fmin((camera->getX() + camera->getWidth()) / DIMS, width);
	int minY = fmax(camera->getY() / DIMS, 0);
	int maxY = fmin((camera->getY() + camera->getHeight()) / DIMS, height);
	for (uint16 i = minX; i <= maxX; ++i) {
		for (uint16 j = minY; j <= maxY; ++j) {
			tiles[map[i * height + j]]->setPosition(i * DIMS, j * DIMS);
			tiles[map[i * height + j]]->render();
		}
	}
}

Map::~Map() {
	delete [] map;
	for (uint16 i = 0; i < NUM_TILES; ++i)
		delete tiles[i];
}