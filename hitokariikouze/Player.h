#pragma once
#include "DxLib.h"
#include "Camera.h"
#include "Fade.h"
class Camera;

class Player
{
private:
	Camera* camera;
	Fade* fade;
public:
	Player();
	~Player();
	void Initialize();
	void Render();
	void Update();
	void Collistion();
	void ReStart();
	VECTOR GetPosition();
	float GetRadius();
	void CameraUpdate();

public:
	VECTOR position,MoveVector;
	float sr,angle,xangle,dangle,oldangle,sangle,speed, oldspeed, dashCount;
	int ModelHandle,DashFlag,DriftFlag;
	bool MoveFlag,ColFlag,isDeadFlag,isEndFlag;
	int KeyPad1,Checkcount;
};


