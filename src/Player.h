#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "TexRect.h"

class Player : public TexRect
{
public:
	Player();
	void update();
	float getYVel();
	void setYVel(float vel);
	float getXVel();
	void setXVel(float vel);
	~Player();
private:
	float yVel, xVel, x, y;
};


#endif