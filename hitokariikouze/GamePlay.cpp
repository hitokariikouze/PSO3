#include "GamePlay.h"
#include "DxLib.h"
#include "Player.h"
#include "SlipStream.h"
#include "Blur.h"

#include "Sound.h"

GamePlay::GamePlay(ISceneChanger * changer) : BaseScene(changer)
{
	player = new Player();
	stage = new Stage(player);
	blur = new BlurScreen();
	slip = new SlipStream();
	effekseer = new EffectEf();
	timer = new Timer();
	fade = new Fade();
	effekseer->Instantiate();

	sound = new Sound();
}

void GamePlay::Initialize()
{
	stage->Initialize();
	player->Initialize();
	timer->Initialize();
	/*blur->InitBlurScreen(blur, 120, -2, -2, 2, 2);

	blur->InitBlurScreen(blur, 240, -2, -2, 2, 2);*/

	effekseer->acceleratorFlag = false;

	sound->playSound(1, DX_PLAYTYPE_LOOP, TRUE);
}

void GamePlay::Update()
{
	timer->CountUpdate();
	player->CameraUpdate();
	if (timer->drawcount <= 0)
	{
		stage->Update();
		player->Update();
		timer->Update();
		if (CheckHitKey(KEY_INPUT_Z))
		{
			mSceneChanger->ChangeScene(eScene_Title);
		}
		if (player->isEndFlag == TRUE)
		{
			player->dashCount = 0;
			player->DashFlag = 0;
			effekseer->Initialize();
			timer->timeFlag = FALSE;
			player->isEndFlag = FALSE;
			mSceneChanger->ChangeScene(eScene_Ending);
			sound->stopSound(1);
			sound->stopSound(3);
			sound->playSound(5, DX_PLAYTYPE_BACK, TRUE);
			sound->DeleteSound();
		}
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
		if (player->dangle > -10)
			sound->playSound(3, DX_PLAYTYPE_BACK, TRUE);
	}
	else if (player->dangle > 0) {
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[3], 0.01 + player->dangle / 60, 0.01 + player->dangle / 70, 0.01 + player->dangle / 80);
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[4], 0.01, 0.01, 0.01);
		if (player->dangle < 10)
			sound->playSound(3, DX_PLAYTYPE_BACK, TRUE);
	}
	else
	{
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[3], 0.01, 0.01, 0.01);
		SetScalePlayingEffekseer3DEffect(effekseer->playingEffectHandle[4], 0.01, 0.01, 0.01);

	}

	if (player->DashFlag == 1)
	{
		BlurScreen::blurFlag = true;
		slip->SlipStreamStart(player->DashFlag = 1);

		stage->Render();
		player->Render();

		if (!sound->CheckSound(4))
			sound->playSound(4, DX_PLAYTYPE_BACK, TRUE);
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