#include "DxLib.h"
#include <math.h>
#include "number.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Stage.h"
#include <string>

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
	SetDrawScreen(DX_SCREEN_BACK);
	hitpoly = 0;
	SetCameraNearFar(0.1f, 1000.0f);
	
	SetBackgroundColor(255, 255, 255);
	sceneManager.Initialize();
	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�����������
		ClearDrawScreen();
		sceneManager.Update();
		sceneManager.Draw();
		
		// ����ʂ̓��e��\��ʂɔ��f������
	    
		ScreenFlip();
	}
	sceneManager.Finalize();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0;
}