#include "AABB.h"
#include "Player.h"


Player::Player(Camera* camera) : TexRect(camera, "res/textures/clatab.png", 0, 0, 0, 32, 32), Entity()
{
	hitbox = new AABB(0, 0, 32, 32);

	walkSpeed = 1.0f;
	jumpSpeed = 1.0f;
	minJumpSpeed = 1.0f;

	pos = glm::vec2(0, 0);
	AABBOffset.y = hitbox->halfSize.y;

	onGround = false;

	currentState = Stand;
}

void Player::update(double deltaTime)
{
	//player movement
	switch (currentState)
	{
	case Stand:
		spd = glm::vec2(0, 0);
		//TODO: Play stand animation
		//if not on ground set jumping
		if (!onGround)
		{
			currentState = Jump;
			break;
		}

		//if left or right pressed set walking
		if (keyState(GoRight) != keyState(GoLeft))
		{
			currentState = Walk;
			break;
		}
		//if jump pressed set jumping and set y speed to jumpSpeed
		else if (keyState(KeyJump))
		{
			spd.y = jumpSpeed;
			currentState = Jump;
			break;
		}
		break;
	case Walk:
		//TODO: Play walk animation
		// if left and right are pressed or neither are pressed set speed to 0 and set standing
		if (keyState(GoRight) == keyState(GoLeft))
		{
			currentState = Stand;
			spd = glm::vec2(0, 0);
			break;
		}
		//if right is pressed set walking unless on right wall and flip sprite
		else if (keyState(GoRight))
		{
			if (pushesRightWall)
				spd.x = 0.0f;
			else
				spd.x = walkSpeed;

			scl.x = fabsf(scale.x);
		}

		//if left is pressed set walking unless on left wall and flip sprite
		else if (keyState(GoLeft))
		{
			if (pushesLeftWall)
				spd.x = 0.0f;
			else
				spd.x = -walkSpeed;

			scl.x = -fabsf(scale.x);
		}
		//if jump is pressed set y speed to jump speed and set jumping
		if (keyState(KeyJump))
		{
			spd.y = jumpSpeed;
			//TODO: play jump sound?
			currentState = Jump;
			break;
		}
		//if not on ground set jumping but dont change speed
		else if (!onGround)
		{
			currentState = Jump;
			break;
		}
		break;
	case Jump:
		//TODO: Play jumping animation
		//update speed from gravity and terminal velocity
		spd.y += gravity * deltaTime;
		spd.y = fmaxf(spd.y, maxFallingSpeed);

		// if left and right are pressed or neither are pressed set speed to 0 and set standing
		if (keyState(GoRight) == keyState(GoLeft))
		{
			currentState = Stand;
			spd = glm::vec2(0, 0);
			break;
		}
		//if right is pressed set walking unless on right wall and flip sprite
		else if (keyState(GoRight))
		{
			if (pushesRightWall)
				spd.x = 0.0f;
			else
				spd.x = walkSpeed;

			scl.x = fabsf(scale.x);
		}

		//if left is pressed set walking unless on left wall and flip sprite
		else if (keyState(GoLeft))
		{
			if (pushesLeftWall)
				spd.x = 0.0f;
			else
				spd.x = -walkSpeed;

			scl.x = -fabsf(scale.x);
		}
		//if jump is not pressed and y speed > 0 clamp speed to min jump speed
		if (!keyState(KeyJump) && spd.y > 0.0f)
			spd.y = fminf(spd.y, minJumpSpeed);
		break;
	case GrabLedge:
		break;
	}

	//update physics
	Entity::update(deltaTime);

	//update pos and scale with physics
	Rect::setPos(roundf(pos.x), roundf(pos.y));
	setScale(scl.x, scl.y);

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
