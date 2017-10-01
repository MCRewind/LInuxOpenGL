#include "Entity.h"

Entity::Entity()
{
	gravity = .6;
	maxFallingSpeed = 1;
	spd = glm::vec2(0, 0);
	pos = glm::vec2(0, 0);
	scl = glm::vec2(1, 1);
}

void Entity::update(double deltaTime)
{
	oldPos = pos;
	oldSpd = spd;

	wasOnGround = onGround;
	pushedRightWall = pushesRightWall;
	pushedLeftWall = pushesLeftWall;
	wasAtCeiling = atCeiling;

	pos.x += spd.x * deltaTime;
	pos.y += spd.y * deltaTime;

	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
		onGround = true;
	}
	else
		onGround = false;

	hitbox->center = pos + AABBOffset;
}