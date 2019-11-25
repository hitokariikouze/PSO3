#include "Player.h"
#include "Camera.h"
#include "number.h"
#include <math.h>

Player::Player()
{
	camera = new Camera(this);
	fade = new Fade();
}

Player::~Player()
{
	delete fade;
}

void Player::Initialize()
{
	speed = 0, oldspeed = 0;
	sr = 80.0f;
	angle = 180.0f, xangle = 0.0f;
	MoveFlag = FALSE, ColFlag = FALSE, isDeadFlag = FALSE,isEndFlag = FALSE;
	DashFlag = 0, DriftFlag = 0;
	camera->Initialize();
	ModelHandle = MV1LoadModel("Tex/Player01.mqo");
	position = VGet(-7900, 10.0, -10000.0);
	MV1SetScale(ModelHandle, VGet(2.0f, 2.0f, 2.0f));
	oldangle = 0.0f, dangle = 0.0f, sangle = 0.0f;
	Checkcount = 0;
}

void Player::Render()
{
	//DrawSphere3D(position, PLAYER_ENUM_DEFAULT_SIZE, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	MV1DrawModel(ModelHandle);
	MV1SetRotationXYZ(ModelHandle, VGet(xangle / 180.0f * DX_PI_F, angle / 180.0f * DX_PI_F, 0.0f));
	MV1SetPosition(ModelHandle, position);
	DrawFormatString(0, 0, GetColor(128, 128, 255), "Position   x%f,y%f,z%f", position.x,position.y,position.z);
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (abs(speed >= 7) && DashFlag != 1)
	{
		speed = oldspeed;
	}
	if (abs(speed >= 11) && DashFlag == 1 )
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
		speed  = 0.0f;
		MoveFlag = TRUE;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		DashFlag = 1;
	}
	else
	{
		DashFlag = 0;
	}
	oldspeed = speed;
	if (CheckHitKey(KEY_INPUT_A) == 1 )
	{
		camera->CameraHAngle += 5.0f;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		camera->CameraVAngle += 5.0f;
	}
	if (dashCount > 0)
	{
		speed += 0.1f;
		dashCount -= 1.0f / 60;
		DashFlag = 1;
		if (camera->Lookdistance <= 260.0)
		{
			camera->Lookdistance += 20.0f;
		}
	}if (dashCount <= 0)
	{
		DashFlag = 0;
	}
	if (DashFlag == 0 && camera->Lookdistance >= CAMERA_LOOK_AT_DISTANCE)
	{
		camera->Lookdistance -= 5.0f;
	}
	//上キーで前に移動
	if (CheckHitKey(KEY_INPUT_UP) == 1 ||  key & PAD_INPUT_A)
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
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || key & PAD_INPUT_RIGHT) {
		camera->CameraHAngle -= 1.0f;
		if (camera->CameraHAngle >= -180.0f)
		{
			camera->CameraHAngle += 360.0f;
		}
		angle += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_RIGHT) == 1 && DriftFlag != 2||
		key & PAD_INPUT_C && key & PAD_INPUT_RIGHT && DriftFlag != 2)
	{
		DriftFlag = 1;
		if (camera->Lookdistance >= 180)
		{
			camera->Lookdistance -= 2.0f;
		}
		if (((dangle >= 20.0f)))
		{
			camera->CameraHAngle -= 1.5f;

			angle += 1.5f;
		}
		else
		{
			dangle += 1.0f;
			camera->CameraHAngle -= 1.5f;

			angle += 2.5f;

		}
		if (camera->CameraHAngle >= -180.0f)
		{
			camera->CameraHAngle += 360.0f;
		}
	}

	//	左キーで左回転させる
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || key & PAD_INPUT_LEFT) {
		camera->CameraHAngle += 1.0f;
		if (camera->CameraHAngle >= 180.0f)
		{
			camera->CameraHAngle -= 360.0f;
		}
		angle -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1 && DriftFlag != 1 ||
		key & PAD_INPUT_C && key & PAD_INPUT_LEFT && DriftFlag != 1)
	{
		DriftFlag = 2;
		if (camera->Lookdistance >= 180)
		{
			camera->Lookdistance -= 2.0f;
		}
		if (((dangle <= -20.0f)))
		{
			camera->CameraHAngle += 1.5f;

			angle -= 1.5f;
		}
		else
		{
			dangle -= 1.0f;
			camera->CameraHAngle += 1.5f;

			angle -= 2.5f;

		}
		if (camera->CameraHAngle >= 180.0f)
		{
			camera->CameraHAngle -= 360.0f;
		}
	}
	//ドリフト解除時
	if (CheckHitKey(KEY_INPUT_C) == 0 || key & PAD_INPUT_C == 0)
	{
		DriftFlag = 0;
		sangle = dangle / 5;
		if (dangle != 0)
		{
			angle = angle - sangle;
			dangle = dangle - sangle;
		}

		if (camera->Lookdistance + 1 < CAMERA_LOOK_AT_DISTANCE)
		{
			camera->Lookdistance += 2.0f;
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
	ReStart();
	
	
}

void Player::Collistion()
{
	
}

void Player::ReStart()
{
	if (position.y <= -300.0f)
	{
		isDeadFlag = TRUE;
	}
	if (isDeadFlag == TRUE)
	{
		speed = 0.0f;
	}
	//1
	if (isDeadFlag == TRUE && position.z >= -11000 && position.z <= -4000 && Checkcount == 0)
	{
		xangle = 0;
		angle = 180;
		camera->CameraHAngle = 0.0f;
		position = VGet(-8000.0f, 40.0f, -10000.0f);
		isDeadFlag = FALSE;

	}
	//2
	if (isDeadFlag == TRUE && position.z >= -4000 && position.z <= 600 && Checkcount == 0)
	{
		xangle = 0;
		angle = 180;
		camera->CameraHAngle = 0.0f;
		position = VGet(-7500.0f, 40.0f, -4000.0f);
		isDeadFlag = FALSE;
	}
	//3
	if (isDeadFlag == TRUE && position.z >= 600 && position.z <= 4000 && Checkcount == 0)
	{
		xangle = 0;
		angle = 180;
		camera->CameraHAngle = 0.0f;
		position = VGet(-8000.0f, 40.0f, 600.0f);
		isDeadFlag = FALSE;
	}
	//4
	if (isDeadFlag == TRUE && position.x >= -6000 && position.x <= 0 && Checkcount == 0)
	{
		xangle = 0;
		angle = 180;
		camera->CameraHAngle = 0.0f;
		position = VGet(-6000.0f, 40.0f, 4000.0f);
		isDeadFlag = FALSE;
	}
	//5
	if (isDeadFlag == TRUE && position.x >= 0 && position.x <= 5000 && Checkcount == 0)
	{
		xangle = 0;
		angle = 0;
		camera->CameraHAngle = 180.0f;
		position = VGet(0.0f, 40.0f, 5300.0f);
		isDeadFlag = FALSE;
	}
	//6
	if (isDeadFlag == TRUE && position.x >= 5000 && position.x <= 8000 ||
		Checkcount >= 1 && isDeadFlag == TRUE)
	{
		xangle = 0;
		angle = 180.0f;
		camera->CameraHAngle = 0.0f;
		position = VGet(5200.0f, 40.0f, 7500.0f);
		isDeadFlag = FALSE;
	}
	//7
	
}



VECTOR Player::GetPosition()
{
	return position;
}

float Player::GetRadius()
{
	return sr;
}

void Player::CameraUpdate()
{
	camera->Update();
}




