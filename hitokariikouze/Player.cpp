#include "Player.h"
#include "Camera.h"
#include <math.h>

Player::Player()
{
	camera = new Camera(this);
}

void Player::Initialize()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	sr = 10.0f;
	angle = 180.0f;
	MoveFlag = FALSE;
	//position = VGet(x, y, z)
	camera->Initialize();
	ModelHandle = MV1LoadModel("CollChara/DxChara.x");
	MV1SetupCollInfo(ModelHandle, -1, 8, 8, 8);
	position = VGet(0.0, 0.0, 0.0);
}

void Player::Render()
{
	//DrawSphere3D(position, sr, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	MV1DrawModel(ModelHandle);
	MV1SetRotationXYZ(ModelHandle, VGet(0.0f, angle / 180.0f * DX_PI_F, 0.0f));
	MV1SetPosition(ModelHandle, position);
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	MoveVector = VGet(0.0f, 0.0f, 0.0f);
	MoveFlag = FALSE;
	if (key &  PAD_INPUT_UP)
	{
		MoveVector.z = 10.0f;
		MoveFlag = TRUE;
	}
	//	下キーで後ろに進む
	if (key & PAD_INPUT_DOWN) {
		MoveVector.z = -10.0f;
		MoveFlag = TRUE;
	}

	//	右キーで右に移動
	if (key & PAD_INPUT_RIGHT) {
		camera->CameraHAngle -= 2.0f;
		if (camera->CameraHAngle >= -180.0f)
		{
			camera->CameraHAngle += 360.0f;
		}
		//x += 2.0f;
		angle += 2.0f;
	}

	//	左キーで左回転させる
	if (key & PAD_INPUT_LEFT) {
		camera->CameraHAngle += 2.0f;
		if (camera->CameraHAngle >= 180.0f)
		{
			camera->CameraHAngle -= 360.0f;
		}
		angle -= 2.0f;
	}
	if (MoveFlag == TRUE)
	{
		VECTOR TempMoveVector;

		// カメラの角度に合わせて移動ベクトルを回転してから加算
		camera->SinParam = sin(camera->CameraHAngle / 180.0f * DX_PI_F);
		camera->CosParam = cos(camera->CameraHAngle / 180.0f * DX_PI_F);
		TempMoveVector.x = MoveVector.x * camera->CosParam - MoveVector.z * camera->SinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = MoveVector.x * camera->SinParam + MoveVector.z * camera->CosParam;

		position = VAdd(position, TempMoveVector);
	}
	camera->Update();
}

VECTOR Player::GetPosition()
{
	return position;
}

float Player::GetRadius()
{
	return sr;
}


