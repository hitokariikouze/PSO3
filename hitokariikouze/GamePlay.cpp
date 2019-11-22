#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"
#include "SlipStream.h"
#include "Blur.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);
	blur = new BlurScreen();
	slip = new SlipStream();
	effekseer = new EffectEf();

}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();

	blur->InitBlurScreen(blur, 240, -2, -2, 2, 2);

	effekseer->acceleratorFlag = false;
}

void GamePlay::Update()
{
	stage->Update();
	player->Update();
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
	Effekseer_Sync3DSetting();

	if (player->DashFlag == 1)
		effekseer->acceleratorFlag = true;
	else
		effekseer->acceleratorFlag = false;
	effekseer->acceleratorFlag = effekseer->EffectSet(effekseer->acceleratorFlag);

	float rotation = player->angle*(3.14 / 180);
	effekseer->SetEffectPosition(0, player->position.x, player->position.y, player->position.z);
	effekseer->SetEffectRotation(0, rotation);
	effekseer->SetEffectPosition(1, player->position.x, player->position.y, player->position.z);
	effekseer->SetEffectRotation(1, rotation);
	effekseer->SetEffectPosition(2, player->position.x, player->position.y, player->position.z);
	effekseer->SetEffectRotation(2, rotation);

	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[0], 0.2, 0.2, 0.2);
	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[1], 0.01 + player->speed*0.02, 0.01 + player->speed*0.02, 0.01 + player->speed*0.04);
	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[2], 0.01 + player->speed*0.04, 0.01 + player->speed*0.04, 0.01 + player->speed*0.04);


	if (player->DashFlag == 1)
	{
		BlurScreen::blurFlag = slip->SlipStreamStart(player->DashFlag == 1, BlurScreen::blurFlag);
		//blur->PreRenderBlurScreen(blur);
		stage->Render();
		player->Render();
		//blur->PostRenderBlurScreen(blur);
	}
	else
	{
		BlurScreen::blurFlag = false;
		stage->Render();
		player->Render();
	}

	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "ゲーム画面です。", GetColor(128, 128, 128));
}