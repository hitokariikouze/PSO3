#pragma once
#include "DxLib.h"
#include "Camera.h"
class Camera;

class Player
{
private:
	Camera* camera;
public:
	Player();
	~Player();
	void Initialize();
	void Render();
	void Update();
	void Collistion();
	VECTOR GetPosition();
	float GetRadius();

public:
	VECTOR position,MoveVector;
	float sr,angle,xangle,dangle,oldangle,sangle,speed, oldspeed;
	int ModelHandle,DashFlag,DriftFlag;
	bool MoveFlag,ColFlag,isDeadFlag;
};


