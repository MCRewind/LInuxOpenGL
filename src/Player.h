#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "Window.h"

#include "TexRect.h"

#include "AABB.h"

class Player : public TexRect
{
public:
	Player(Window * window, Camera* camera);
	void update();
	AABB * getHitbox();
	void alignHitbox();
	void landed();
	void setGravity(float gravity);
	~Player();
private:
	Window * window;
	AABB * hitbox;
	bool jump = false;
	float gravity, velY;
};

#endif