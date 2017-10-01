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
		GoLeft = 0,
		GoRight,
		GoDown,
		KeyJump,
		Count
	};
	enum PlayerState
	{
		Stand,
		Walk,
		Jump,
		GrabLedge
	};
	PlayerState currentState;
	float jumpSpeed, walkSpeed, minJumpSpeed;
	bool prevInputs[4];
	bool inputs[4];
protected:
	bool released(KeyInput key);
	bool keyState(KeyInput key);
	bool pressed(KeyInput key);
private:
};



#endif