#define __STDC_WANT_LIB_EXT1__ 1
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>

#include <fstream>
#include <Windows.h>
#include <vector>
/*#include <stdio.h>
#include <errno.h>
#include <string.h>*/

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
	map = std::vector<int>(width * height);
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
	setMap("res/bmps/16.bmp");
	player = new Player(window, camera);
}

void Map::update() {

	camera->setPos(glm::vec3(player->getX() - camera->getWidth()/2, player->getY() - camera->getHeight() / 2, 0));
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
			if ((i * height + j) < map.size())
			{
				tiles[map[i * height + j]]->setPosition(i * DIMS, j * DIMS);
				tiles[map[i * height + j]]->render();
			}
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
	ofn.lpstrFilter = "Bitmap Files\0*.bmp\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a Bitmap";
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

	setMap(filename);
	//read canvas from map file
	//open selected file in read mode
	/*std::ifstream infile;
	infile.open(filename, std::ios::binary);
	std::vector<char> buffer((
		std::istreambuf_iterator<char>(infile)),
		(std::istreambuf_iterator<char>()));*/
}

void Map::setMap(char* filename)
{
	//read canvas from bmp file
	bitmap_image inmap = readBMPCanvas(filename);
	width = inmap.width();
	height = inmap.height();
	map.clear();
	map.resize(width * height);

	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < height; ++j)
		{
			rgb_t color;
			inmap.get_pixel(i, j, color);
			map[i * height + j] = getTileFromRed(color.red);
		}
}

int Map::getTileFromRed(int8 red)
{
	switch (red)
	{
	case 0:
		return 1;
		break;
	case 255:
		return 0;
		break;
	default:
		return 0;
	}
}

bitmap_image Map::readBMPCanvas(char* filename)
{
	int i;
	/*FILE *f;
	errno_t err;


	if ((err = fopen_s(&f, filename, "r")) != 0) {
		#ifdef __STDC_LIB_EXT1__
		char buf[strerrorlen_s(err) + 1];
		fprintf(stderr, "cannot open file '%s': %s\n",
			filename, strerror_s(err, buf, sizeof buf));
		strerror_s(buf, sizeof buf, err);
		fprintf_s(stderr, "cannot open file '%s': %s\n",
			filename, buf);
		#endif
	}
	else {
		// File was opened, f can be used to read the stream.
	}*/

	bitmap_image image(filename);
	/*FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

											   // extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}*/

	return image;
}

Map::~Map() {
	map.clear();
	map.shrink_to_fit();
	for (uint16 i = 0; i < NUM_TILES; ++i)
		delete tiles[i];
}