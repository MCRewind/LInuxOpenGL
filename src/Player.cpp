#include "AABB.h"
#include "Player.h"
#include <iostream>

Player::Player(Camera* camera) : TexRect(camera, "res/textures/clatab.png", 0, 0, 0, 32, 32)
{
	gravity = .5f;
	terminalV = 3;
	velocity = glm::vec2(0, 0);
	pos = glm::vec2(5, 0);
	hitbox = new AABB(pos.x, pos.y, 32, 32);
}

void Player::update(double deltaTime)
{
	velocity.x = 0;

	if (keyState(GoRight) != keyState(GoLeft)) 
	{
		if (keyState(GoRight))
		{
			velocity.x = 1;
		}

		if (keyState(GoLeft))
		{
			velocity.x = -1;
		}
	}

	if (pressed(KeyJump))
	{
		if (onGround)
		{
			velocity.y = -6.0f;
			onGround = false;
		}
	}

	if (released(KeyJump))
	{
		if (velocity.y < -3.0f)
		{
			velocity.y = -3.0f;
		}
	}

	velocity.y += gravity * deltaTime;
	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;
	//velocity.y = fmaxf(velocity.y, terminalV);

	if (pos.y > 16.0f)
	{
		pos.y = 16.0f;
		velocity.y = 0.0f;
		onGround = true;
	}
	//std::cout << pos.x << std::endl;
	hitbox->setPos(pos.x, pos.y);
	std::cout << hitbox->getPos().x << std::endl;

	//update pos and scale with physics
	//Rect::setPos(roundf(pos.x), roundf(pos.y));
	position = glm::vec3(pos, 0);

	//update previous inputs
	memcpy(prevInputs, inputs, sizeof(prevInputs));
}

//checks if last frames input has key and this frames doesnt
bool Player::released(KeyInput key)
{
	return (!inputs[(int)key] && prevInputs[(int)key]);
}

//checks if current frames input has key
bool Player::keyState(KeyInput key)
{
	return (inputs[(int)key]);
}

//checks if current frames input has key and last frames doesnt
bool Player::pressed(KeyInput key)
{
	return (inputs[(int)key] && !prevInputs[(int)key]);
}

Player::~Player()
{

}
