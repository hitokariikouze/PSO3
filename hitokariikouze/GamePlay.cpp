#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"
#include "Timer.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);
	timer = new Timer();
}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();
	timer->Initialize();
}

void GamePlay::Update()
{
	stage->Update();
	player->Update();
	timer->Update();
	
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
	timer->Render();
	
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�Q�[����ʂł��B", GetColor(128, 128, 128));
}
