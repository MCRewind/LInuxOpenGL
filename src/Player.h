#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "TexRect.h"

class Player : public TexRect
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
	glm::vec2 pos, velocity;
	float gravity, terminalV;
	bool onGround;
protected:
	bool keyState(KeyInput key);
	bool pressed(KeyInput key);
	bool released(KeyInput key);
private:
};



#endif