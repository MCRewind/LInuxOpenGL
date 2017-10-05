#include "AABBUtils.h"
#include <iostream>

bool checkCollisions(int map[5][5], AABB* hitbox, float pX, float pY, float &x, float &y)
{
	int left_tile = fmaxf(0, floor(x / 16));
	int right_tile = ceil((x / 16) + 16);
	int top_tile = fmaxf(0, floor(y / 16));
	int bottom_tile = fminf(ceil((y / 16) + 16), 5);

	std::cout << left_tile << ", " << right_tile << ", " << top_tile << ", " << bottom_tile << std::endl;

	for (int i = left_tile; i <= right_tile; i++)
		for (int j = top_tile; j < bottom_tile; j++)
		{
			if (map[i][j] == 1)
			{
				std::cout << "collided" << std::endl;
				int dx = (i * 16) - x;
				int dy = (j * 16) - y;
				if (abs(dy) < abs(dx))
					y += dy;
				else
					x += dx;
				return true;
			}
		}
	return false;
}