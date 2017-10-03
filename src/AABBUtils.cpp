#include "AABBUtils.h"

bool checkCollisions(int map[5][5], AABB* hitbox, float pX, float pY, float &x, float &y)
{
	int left_tile = (x) / 16;
	int right_tile = (x + 2*(hitbox->halfSize.x)) / 16;
	int top_tile = (y) / 16;
	int bottom_tile = (y + 2*(hitbox->halfSize.y)) / 16;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > 5) right_tile = 5;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > 5) bottom_tile = 5;

	for (int i = left_tile; i <= right_tile; i++)
		for (int j = top_tile; j < bottom_tile; j++)
			if (map[i][j] == 1)
			{
				int dx = x - ((i * 16) + 16);
				int dy = x - ((j * 16) + 16);
				if (abs(dy) < abs(dx))
					y += dy;
				else
					x += dx;
				return true;
			}
	return false;
}