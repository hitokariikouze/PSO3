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
	void Initialize();
	void Render();
	void Update();
	void Collistion();
	VECTOR GetPosition();
	float GetRadius();

public:
	VECTOR position;
	VECTOR MoveVector;
	VECTOR Sposition;
	float sr,x,y,z,angle;
	int ModelHandle;
	bool MoveFlag,ColFlag;
};


