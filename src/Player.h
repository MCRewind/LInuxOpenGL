#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "TexRect.h"
#include "Entity.h"

class Player : public TexRect, public Entity
{
public:
	Player(Camera* camera);
	void update(double deltaTime);
	~Player();
	enum KeyInput
	{
		GoLeft,
		GoRight,
		GoDown,
		KeyJump,
	};
	float jumpSpeed, walkSpeed, minJumpSpeed;
	bool inputs[4];
	bool prevInputs[4];
	AABB* hitbox;
protected:
	bool keyState(KeyInput key);
	bool pressed(KeyInput key);
	bool released(KeyInput key);
private:
};



#endif