#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"
#include "SlipStream.h"
#include "Blur.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);

	slip = new SlipStream();
	effekseer = new EffectEf();

	effekseer->Instantiate();

}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();

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
	for (int i = 0; i < 3; i++)
	{
		effekseer->SetEffectPosition(i, player->position.x, player->position.y, player->position.z);
		effekseer->SetEffectRotation(i, rotation);
	}
	effekseer->SetEffectPosition(3, player->position.x, player->position.y, player->position.z);
	effekseer->SetEffectPosition(4, player->position.x, player->position.y, player->position.z);
	effekseer->SetEffectRotation(3, rotation - 150 * (3.14 / 180));
	effekseer->SetEffectRotation(4, rotation + 150 * (3.14 / 180));

	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[0], 0.2, 0.2, 0.2);
	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[1], 0.01 + player->speed*0.02, 0.01 + player->speed*0.02, 0.01 + player->speed*0.04);
	SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[2], 0.01 + player->speed*0.04, 0.01 + player->speed*0.04, 0.01 + player->speed*0.04);
	if (player->dangle < 0) {
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[3], 0.01, 0.01, 0.01);
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[4], 0.01 + player->dangle / -60, 0.01 + player->dangle / -70, 0.01 + player->dangle / -80);
	}
	else if (player->dangle > 0) {
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[3], 0.01 + player->dangle / 60, 0.01 + player->dangle / 70, 0.01 + player->dangle / 80);
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[4], 0.01, 0.01, 0.01);
	}
	else
	{
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[3], 0.01, 0.01, 0.01);
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[4], 0.01, 0.01, 0.01);
	}



	if (player->DashFlag == 1)
	{
		BlurScreen::blurFlag = true;
		slip->SlipStreamStart(player->DashFlag == 1);
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