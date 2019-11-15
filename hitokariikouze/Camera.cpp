#include "Camera.h"
#include "number.h"
#include <math.h>
#include "Player.h"

Camera::Camera(Player* player)
{
	m_player = player;
}

void Camera::Initialize()
{
	float CameraHAngle = 0.0f;
	float CameraVAngle = 40.0f;
	SetCameraNearFar(100.0f, 50000.0f);
}

void Camera::Render()
{
}

void Camera::Update()
{
	Chase();
}

void Camera::Chase()
{
	VECTOR CameraPosition;
	VECTOR CameraLookAtPosition;

	CameraLookAtPosition = m_player->GetPosition();
	CameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

	SinParam = sin(CameraVAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraVAngle / 180.0f * DX_PI_F);
	TempPosition1.x = 0.0f;
	TempPosition1.y = SinParam * CAMERA_LOOK_AT_DISTANCE;
	TempPosition1.z = -CosParam * CAMERA_LOOK_AT_DISTANCE;

	SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
	TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z;
	TempPosition2.y = TempPosition1.y;
	TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z;

	CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

	SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
}