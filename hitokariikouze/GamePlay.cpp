#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
}

void GamePlay::Initialize()
{
	player->Initialize();
}

void GamePlay::Update()
{
	player->Update();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		mSceneChanger->ChangeScene(eScene_Ending);
	}
}

void GamePlay::Draw()
{
	player->Render();
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "ゲーム画面です。", GetColor(128, 128, 128));
}
