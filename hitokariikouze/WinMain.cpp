#include "DxLib.h"
#include <math.h>
#include "number.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Stage.h"
#include <string>
#include <EffekseerForDXLib.h>
#include "BaseScene.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	SceneManager sceneManager;

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

	// Effekseer������������B
		// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	hitpoly = 0;
	SetCameraNearFar(0.1f, 1000.0f);

	SetBackgroundColor(255, 255, 255);
	sceneManager.Initialize();

	BlurScreen blur;
	blur.InitBlurScreen(&blur, 180, -2, -2, 2, 2);

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();

		if (blur.blurFlag) {
			blur.PreRenderBlurScreen(&blur);
			sceneManager.Update();
			sceneManager.Draw();
			blur.PostRenderBlurScreen(&blur);
		}
		else
		{
			sceneManager.Update();
			sceneManager.Draw();
		}

		UpdateEffekseer3D();
		DrawEffekseer3D();

		// ����ʂ̓��e��\��ʂɔ��f������

		ScreenFlip();
	}
	sceneManager.Finalize();

	// Effekseer���I������B
	Effkseer_End();

	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0;
}