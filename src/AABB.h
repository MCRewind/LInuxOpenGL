#ifndef __AABB_H_
#define __AABB_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AABB
{
public:
	AABB(float x, float y, float width, float height);
	bool overlaps(AABB other);
	glm::vec2 getPos();
	void setPos(float x, float y);
	glm::vec2 center, halfSize;
};

#endif