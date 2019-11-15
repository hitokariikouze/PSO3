#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);
}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();
	
}

void GamePlay::Update()
{
	stage->Update();
	player->Update();
	
	if (CheckHitKey(KEY_INPUT_Z))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		mSceneChanger->ChangeScene(eScene_Ending);
	}
}

void GamePlay::Draw()
{
	stage->Render();
	player->Render();
	
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(128, 128, 128));
}
