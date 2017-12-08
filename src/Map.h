#ifndef MAP
#define MAP

#include "Types.h"

#include "Window.h"
#include "Camera.h"

#include <vector>
#include "bitmap_image.hpp"

#include "Player.h"
#include "Tile.h"

class Map {
	public:
		Map(Window * window, Camera * camera, uint16 width, uint16 height);
		void update();
		bool checkCollision();
		void render();
		void importCanvas();
		struct BMPData
		{
			int width;
			int height;
			uint8* image;
		};
		bitmap_image readBMPCanvas(char* filename);
		int getTileFromRed(int8 red);
		void setMap(char* filename);
		~Map();
	private:
		const static uint16 NUM_TILES = 2;
		const uint8 DIMS = 16;
		Camera * camera;
		Window * window;
		Player * player;
		Tile * tiles[NUM_TILES];
		std::vector<int> map;
		uint16 width, height;
};

#endif