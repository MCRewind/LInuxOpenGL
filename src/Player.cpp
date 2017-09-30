#include "Player.h"

Player::Player() : TexRect(camera, "res/textures/test.png", 100, 100, 0, 16, 16)
{
	
}

void Player::update()
{
	yVel += .1f;
	x += xVel;
	y += yVel;
	Rect::setPos(x, y);
}

float Player::getXVel()
{
	return xVel;
}

void Player::setXVel(float vel)
{
	xVel = vel;
}

void Player::setYVel(float vel)
{
	yVel = vel;
}

float Player::getYVel()
{
	return yVel;
}

Player::~Player()
{

}
