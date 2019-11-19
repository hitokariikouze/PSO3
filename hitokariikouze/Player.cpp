#include "Player.h"
#include "Camera.h"
#include "number.h"
#include <math.h>

Player::Player()
{
	camera = new Camera(this);
}

void Player::Initialize()
{
	speed = 0;
	oldspeed = 0;
	sr = 80.0f;
	angle = 180.0f;
	xangle = 0.0f;
	MoveFlag = FALSE;
	ColFlag = FALSE;
	isDeadFlag = FALSE;
	DashFlag = 0;
	camera->Initialize();
	ModelHandle = MV1LoadModel("Tex/Car_Smale.mqo");
	position = VGet(1200.0, 40.0, 0.0);
	oldangle = 0.0f;
	dangle = 0.0f;
	sangle = 0.0f;
}

void Player::Render()
{
	DrawSphere3D(position, PLAYER_ENUM_DEFAULT_SIZE, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	
	MV1DrawModel(ModelHandle);
	MV1SetRotationXYZ(ModelHandle, VGet(xangle / 180.0f * DX_PI_F, angle / 180.0f * DX_PI_F, 0.0f));
	MV1SetPosition(ModelHandle, position);
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (abs(speed >= 10))
	{
		speed = oldspeed;
	}
	MoveVector = VGet(0.0f, 0.0f, 0.0f + speed);
	if (ColFlag == FALSE)
	{
		MoveVector.y = -5.0f;
		if (xangle >= -80)
		{
			xangle -= 0.5f;
		}
		
		MoveFlag = TRUE;
	}
	
	oldspeed = speed;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		camera->CameraHAngle += 5.0f;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		camera->CameraVAngle += 5.0f;
	}
	if (DashFlag == 1)
	{
		speed += 0.1f;
		if (camera->Lookdistance <= 300)
		{
			camera->Lookdistance += 2.5f;
		}
	}
	if(DashFlag == 0 && camera->Lookdistance >= CAMERA_LOOK_AT_DISTANCE)
	{
		camera->Lookdistance -= 1.5f;
		
	}
	if (CheckHitKey(KEY_INPUT_UP) == 1 )
	{
		if (ColFlag == TRUE)
		{
			MoveFlag = TRUE;
			speed += 0.05f;
		}
	}
	else
	{
		if (speed >= 0)
		{
			speed -= 0.05f;
		}
	}
	//	右キーで右に移動
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		camera->CameraHAngle -= 1.0f;
		if (camera->CameraHAngle >= -180.0f)
		{
			camera->CameraHAngle += 360.0f;
		}
		angle += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		if (camera->Lookdistance >= 160)
		{
			camera->Lookdistance -= 1.0f;
		}
		if (((dangle >= 20.0f)))
		{
			camera->CameraHAngle -= 1.0f;

			angle += 1.0f;
		}
		else
		{
			dangle += 1.0f;
			camera->CameraHAngle -= 1.0f;

			angle += 2.0f;

		}
		if (camera->CameraHAngle >= -180.0f)
		{
			camera->CameraHAngle += 360.0f;
		}
	}

	//	左キーで左回転させる
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		camera->CameraHAngle += 1.0f;
		if (camera->CameraHAngle >= 180.0f)
		{
			camera->CameraHAngle -= 360.0f;
		}
		angle -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		if (camera->Lookdistance >= 160)
		{
			camera->Lookdistance -= 1.0f;
		}
		if (((dangle <= -20.0f)))
		{
			camera->CameraHAngle += 1.0f;

			angle -= 1.0f;
		}
		else
		{
			dangle -= 1.0f;
			camera->CameraHAngle += 1.0f;

			angle -= 2.0f;

		}
		if (camera->CameraHAngle >= 180.0f)
		{
			camera->CameraHAngle -= 360.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_C) == 0 )
	{
		sangle = dangle / 8;
		if (dangle != 0)
		{
			angle = angle - sangle;
			dangle = dangle - sangle;
		}
		
		if (camera->Lookdistance + 1 < CAMERA_LOOK_AT_DISTANCE )
		{
			camera->Lookdistance += 1.0f;
		}
	}
	
	if (MoveFlag == TRUE)
	{
		VECTOR TempMoveVector;

		// カメラの角度に合わせて移動ベクトルを回転してから加算
		camera->SinParam = sin(camera->CameraHAngle / 180.0f * DX_PI_F);
		camera->CosParam = cos(camera->CameraHAngle / 180.0f * DX_PI_F);
		TempMoveVector.x = MoveVector.x * camera->CosParam - MoveVector.z * camera->SinParam;
		TempMoveVector.y = MoveVector.y;
		TempMoveVector.z = MoveVector.x * camera->SinParam + MoveVector.z * camera->CosParam;

		position = VAdd(position, TempMoveVector);
	}
	camera->Update();
	if (position.y <= -700.0f)
	{
		isDeadFlag = TRUE;
	}
	DrawFormatString(0, 0, GetColor(128, 128, 128), " angle %d", dangle); 
}

void Player::Collistion()
{

}



VECTOR Player::GetPosition()
{
	return position;
}

float Player::GetRadius()
{
	return sr;
}


