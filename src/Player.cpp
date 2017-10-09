#include "Player.h"

extern double utime;

Player::Player(Window * window, Camera* camera) : TexRect(camera, "res/textures/clatab.png", 0, 0, 0, 32, 32)
{
	gravity = .5f;
	hitbox = new AABB(position.x, position.y, 32, 32);
}

void Player::update() {
	float speed = (float)(64 * utime);
	if (window->keyPressed(GLFW_KEY_D)) position.x += speed;
	if (window->keyPressed(GLFW_KEY_A)) position.x -= speed;
	if (window->keyPressed(GLFW_KEY_SPACE) && !jump) {
		velY = -256;
		jump = true;
	}
	velY += gravity;
	position.y += velY * utime;
	hitbox->setPosition(position);
}

AABB * Player::getHitbox() {
	return hitbox;
}

void Player::alignHitbox() {
	hitbox->setPosition(position);
}

void Player::landed() {
	velY = 0;
	jump = false;
}

void Player::setGravity(float gravity) {
	this->gravity = gravity;
}

Player::~Player() {
	delete hitbox;
}