#include "Player.h"

extern double deltaTime;

Player::Player(Window * window, Camera* camera) : TexRect(camera, "res/textures/clatab.png", 0, 0, 0, 32, 32)
{
	this->window = window;
	gravity = .5f;
	hitbox = new AABB(position.x, position.y, 32, 32);
}

void Player::update() {
	float speed = (float)(64 * deltaTime);
	if (window->isKeyPressed(GLFW_KEY_D)) position.x += speed;
	if (window->isKeyPressed(GLFW_KEY_A)) position.x -= speed;
	if (window->isKeyPressed(GLFW_KEY_SPACE) && !jump) {
		velY = -256;
		jump = true;
	}
	velY += gravity;
	position.y += velY * deltaTime;
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