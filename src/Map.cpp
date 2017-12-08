#include <iostream>
#include <math.h>

#include <fstream>
#include <Windows.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include "AABB.h"

#include "Map.h"

Map::Map(Window * window, Camera * camera, uint16 width, uint16 height) {
	this->camera = camera;
	this->window = window;
	this->width = width;
	this->height = height;
	map = new uint16[width * height];
	tiles[0] = new Tile(camera, "res/textures/sky_tile.png", false, 0, DIMS, DIMS);
	tiles[1] = new Tile(camera, "res/textures/stone_tile.png", true, 0, DIMS, DIMS);
	for (uint16 i = 0; i < width; i++)
		for (uint16 j = 0; j < height; j++)
		{
			if (j == height-1 || j == 0 || i == 0 || i == width - 1)
				map[i * height + j] = 1;
			else
				map[i * height + j] = 0;
		}
	player = new Player(window, camera);
}

void Map::update() {

	camera->setPos(glm::vec3(player->getX() - camera->getWidth()/2, camera->getPos().y, 0));
	player->update();
	while (checkCollision());
}

bool Map::checkCollision() {
	AABB * playerHit = player->getHitbox();
	AABB * closest = 0;
	AABB * current = 0;
	glm::vec3 closestLength;
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
						closest = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
						closestLength = closest->getCenter() + (-playerHit->getCenter());
					}
					else {
						if (current)
							delete current;
						current = new AABB(i * DIMS, j * DIMS, DIMS, DIMS);
						glm::vec3 curLength = current->getCenter() + (-playerHit->getCenter());
						if (glm::length2(curLength) < glm::length2(closestLength)) {
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
			glm::vec3 transform = closest->getTransform(playerHit);
			if ((player->getVelocity().y < 0 && transform.y < 0) || (player->getVelocity().y > 0 && transform.y > 0)) {
				transform.x = closest->getTransformX(playerHit);
				transform.y = 0;
			}
			else if ((player->getVelocity().x < 0 && transform.x < 0) || (player->getVelocity().x > 0 && transform.x > 0)) {
				transform.y = closest->getTransformY(playerHit);
				transform.x = 0;
			}
			player->translate(transform);
			player->alignHitbox();
			if (transform.y < 0)
				player->hitBottom();
			else if (transform.x > 0)
				player->hitLeft();
			else if (transform.x < 0)
				player->hitRight();
			else
				player->hitTop();
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
	int minX = fmax(-camera->getPos().x / DIMS, 0);
	int maxX = fmin((-camera->getPos().x + camera->getWidth()) / DIMS, width);
	int minY = fmax(-camera->getPos().y / DIMS, 0);
	int maxY = fmin((-camera->getPos().y + camera->getHeight()) / DIMS, height);
	for (uint16 i = minX; i <= maxX; ++i) {
		for (uint16 j = minY; j <= maxY; ++j) {
			tiles[map[i * height + j]]->setPosition(i * DIMS, j * DIMS);
			tiles[map[i * height + j]]->render();
		}
	}
}

void Map::importCanvas()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Map Files\0*.sbm\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a Map";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}

	//read canvas from map file
	//open selected file in read mode
	std::ifstream infile;
	infile.open(filename, std::ios::binary);
	std::vector<char> buffer((
		std::istreambuf_iterator<char>(infile)),
		(std::istreambuf_iterator<char>()));
}


Map::~Map() {
	delete [] map;
	for (uint16 i = 0; i < NUM_TILES; ++i)
		delete tiles[i];
}