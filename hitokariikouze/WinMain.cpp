#include "DxLib.h"
#include <math.h>
#include "number.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"
#include <string>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	Player player;
	SceneManager sceneManager;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	int StageHandle;
	bool Hitflag = false;
	VECTOR  SpherePos2;
	int hitpoly;
	ChangeWindowMode(true);
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(640, 480, 16);
	if (DxLib_Init() == -1) // �c�w���C�u��������������
	{
		return -1; // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	hitpoly = 0;
	SetCameraNearFar(0.1f, 1000.0f);
	StageHandle = MV1LoadModel("Tex/Test.mqo");
	MV1SetScale(StageHandle, VGet(500.0f, 500.0f, 500.0f));
	SetBackgroundColor(255, 255, 255);
	sceneManager.Initialize();
	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();
		sceneManager.Update();
		sceneManager.Draw();
		{
			int i;
			VECTOR Pos1;
			VECTOR Pos2;

			SetUseZBufferFlag(TRUE);

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
			for (i = 0; i <= LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(128, 128, 128));
				Pos1.x += LINE_AREA_SIZE / LINE_NUM;
				Pos2.x += LINE_AREA_SIZE / LINE_NUM;
			}

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			for (i = 0; i < LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(128, 128, 128));
				Pos1.z += LINE_AREA_SIZE / LINE_NUM;
				Pos2.z += LINE_AREA_SIZE / LINE_NUM;
			}

			SetUseZBufferFlag(FALSE);
		}
		MV1DrawModel(StageHandle);
		// ����ʂ̓��e��\��ʂɔ��f������
		/*MV1CollResultPolyDimTerminate(HitPolyDim);*/
		ScreenFlip();
	}
	sceneManager.Finalize();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0;
}