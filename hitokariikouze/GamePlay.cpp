#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);
	blur = new BlurScreen();
}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();
	blur->InitBlurScreen(blur, 120, -2, -2, 2, 2);
}

void GamePlay::Update()
{
	stage->Update();
	player->Update();
	/*if (player->DashFlag == 0 && !blur->blurFlag)
	{
		
	}*/
	/*else
	{
		stage->Update();
		player->Update();
		blur->PreRenderBlurScreen(blur);
		
		blur->PostRenderBlurScreen(blur);
	}*/
	if (CheckHitKey(KEY_INPUT_Z))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	if (player->isDeadFlag == TRUE)
	{
		mSceneChanger->ChangeScene(eScene_Ending);
	}
}

void GamePlay::Draw()
{
	stage->Render();
	player->Render();
	
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "ゲーム画面です。", GetColor(128, 128, 128));
}
