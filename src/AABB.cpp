#include "AABB.h"

AABB::AABB(float x, float y, float width, float height)
{
	center = glm::vec3(x + width / 2, y + height / 2, 0);
	halfSize = glm::vec3(width / 2, height / 2, 0);
}

bool AABB::overlaps(AABB* other)
{
	if (abs(center.x - other->center.x) > halfSize.x + other->halfSize.x) return false;
	if (abs(center.y - other->center.y) > halfSize.y + other->halfSize.y) return false;
	return true;
}