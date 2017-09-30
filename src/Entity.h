#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <glm/glm.hpp>
#include "AABB.h"

class Entity
{
public:
	Entity();
	glm::vec2 oldPos, pos, oldSpd, spd, scale, AABBOffset;
	AABB* AABB;
	bool pushedRightWall, pushesRightWall, pushedLeftWall, pushesLeftWall, wasOnGround, onGround, wasAtCeiling, atCeiling;
	void update();
};

#endif