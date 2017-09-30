#include "Entity.h"

Entity::Entity()
{

}

void Entity::update()
{
	oldPos = pos;
	oldSpd = spd;

	wasOnGround = onGround;
	pushedRightWall = pushesRightWall;
	pushedLeftWall = pushesLeftWall;
	wasAtCeiling = atCeiling;

	pos += spd;
}