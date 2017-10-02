#include "Entity.h"

Entity::Entity()
{
	gravity = .5f;
	terminalV = 3;
	velocity = glm::vec2(0, 0);
	pos = glm::vec2(0, 1);
}

void Entity::update(double deltaTime)
{
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;
	velocity.y += gravity * deltaTime;
	//velocity.y = fmaxf(velocity.y, terminalV);

	if (pos.y > 0.0f)
	{
		pos.y = 0.0f;
		velocity.y = 0.0f;
		onGround = true;
	}

	hitbox->center = pos;
}