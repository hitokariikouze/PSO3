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
	VECTOR GetPosition();
	float GetRadius();

public:
	VECTOR position;
	VECTOR MoveVector;
	float sr,x,y,z,angle;
	int ModelHandle;
	bool MoveFlag;
};


