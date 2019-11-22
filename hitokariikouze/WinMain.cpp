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
	SetGraphMode(800, 640, 16);
	if (DxLib_Init() == -1) // �c�w���C�u��������������
	{
		return -1; // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	hitpoly = 0;
	//SetCameraNearFar(0.1f, 50000.0f);
	
	SetBackgroundColor(128, 128, 128);
	sceneManager.Initialize();
	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);
	// ���[�v
	while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		sceneManager.Update();
		sceneManager.Draw();
		
		// ����ʂ̓��e��\��ʂɔ��f������
	    
		ScreenFlip();
	}
	sceneManager.Finalize();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0;
}