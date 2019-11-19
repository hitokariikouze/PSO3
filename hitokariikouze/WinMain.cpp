#include "DxLib.h"
#include <math.h>
#include "number.h"
#include "Player.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Stage.h"
#include <string>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	
	SceneManager sceneManager;
	
	
	bool Hitflag = false;
	VECTOR  SpherePos2;
	int hitpoly;
	ChangeWindowMode(true);
	// 画面モードのセット
	SetGraphMode(640, 480, 16);
	if (DxLib_Init() == -1) // ＤＸライブラリ初期化処理
	{
		return -1; // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	hitpoly = 0;
	SetCameraNearFar(0.1f, 1000.0f);
	
	SetBackgroundColor(255, 255, 255);
	sceneManager.Initialize();
	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
		ClearDrawScreen();
		sceneManager.Update();
		sceneManager.Draw();
		
		// 裏画面の内容を表画面に反映させる
	    
		ScreenFlip();
	}
	sceneManager.Finalize();
	DxLib_End(); // ＤＸライブラリ使用の終了処理

	return 0;
}