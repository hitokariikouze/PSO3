#pragma once
#include "DxLib.h"
#include "Player.h"
class Player;


class Camera 
{
private:
	Player* m_player;
public:

	Camera(Player* player);
	void Initialize();
	void Render();
	void Update();
	void Chase();

public:
	float CameraHAngle;
	float CameraVAngle;
	float  SinParam;
	float  CosParam;
	VECTOR TempPosition1;
	VECTOR TempPosition2;
};
