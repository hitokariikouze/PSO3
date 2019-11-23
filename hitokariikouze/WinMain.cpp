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

	// Effekseerを初期化する。
		// 引数には画面に表示する最大パーティクル数を設定する。
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

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化する
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

		// 裏画面の内容を表画面に反映させる

		ScreenFlip();
	}
	sceneManager.Finalize();

	// Effekseerを終了する。
	Effkseer_End();

	DxLib_End(); // ＤＸライブラリ使用の終了処理

	return 0;
}