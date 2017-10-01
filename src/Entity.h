#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <glm/glm.hpp>
#include "AABB.h"

class Entity
{
public:
	Entity();
	glm::vec2 oldPos, pos, oldSpd, spd, scl, AABBOffset;
	AABB* hitbox;
	float gravity, maxFallingSpeed;
	bool pushedRightWall, pushesRightWall, pushedLeftWall, pushesLeftWall, wasOnGround, onGround, wasAtCeiling, atCeiling;
	void update(double deltaTime);
};

#endif