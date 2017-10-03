#ifndef __AABB_H_
#define __AABB_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AABB
{
public:
	AABB(glm::vec2 center, glm::vec2 halfSize);
	bool overlaps(AABB* other);
	glm::vec2 center, halfSize;
};

#endif