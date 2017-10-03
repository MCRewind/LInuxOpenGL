#include "Entity.h"

Entity::Entity()
{
	gravity = .5f;
	terminalV = 3;
	velocity = glm::vec2(0, 0);
	pos = glm::vec2(0, 10);
	hitbox = new AABB(glm::vec2(16, 16), glm::vec2(16, 16));
}

void Entity::update(double deltaTime)
{
	velocity.y += gravity * deltaTime;
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;
	//velocity.y = fmaxf(velocity.y, terminalV);

	if (pos.y > 0.0f)
	{
		pos.y = 0.0f;
		velocity.y = 0.0f;
		onGround = true;
	}

	hitbox->center = pos;
}