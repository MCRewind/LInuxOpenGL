#include "AABB.h"
#include "Player.h"


Player::Player(Camera* camera) : TexRect(camera, "res/textures/clatab.png", 0, 0, 0, 32, 32), Entity()
{
	hitbox = new AABB(glm::vec2(16, 16), glm::vec2(16, 16));
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



	//update physics
	Entity::update(deltaTime);

	//update pos and scale with physics
	Rect::setPos(roundf(pos.x), roundf(pos.y));

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
