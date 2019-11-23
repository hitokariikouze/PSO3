#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Blur.h"

class Player;

class Camera
{
private:
	Player* m_player;

public:

	Camera(Player* player);
	~Camera();
	void Initialize();
	void Render();
	void Update();
	void Chase();

	BlurScreen* blur;
public:
	float Lookdistance;
	float Lookheight;
	float CameraHAngle;
	float CameraVAngle;
	float  SinParam;
	float  CosParam;
	VECTOR TempPosition1;
	VECTOR TempPosition2;

};

