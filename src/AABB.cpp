#include "AABB.h"

AABB::AABB(glm::vec2 center, glm::vec2 halfSize)
{
	this->center = center;
	this->halfSize = halfSize;
}

bool AABB::overlaps(AABB* other)
{
	if (abs(center.x - other->center.x) > halfSize.x + other->halfSize.x) return false;
	if (abs(center.y - other->center.y) > halfSize.y + other->halfSize.y) return false;
	return true;
}