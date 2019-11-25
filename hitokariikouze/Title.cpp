#include "Title.h"
#include "DxLib.h"
#include "Sound.h"

Title::Title(ISceneChanger * changer) : BaseScene(changer)
{
	fade = new Fade();
	sound = new Sound();
	sound->playSound(0, DX_PLAYTYPE_LOOP, TRUE);
}

void Title::Initialize()
{
	fade->Initialize();
	grHandle = LoadGraph("Tex/PS03_title.png");
}

void Title::Update()
{


}

void Title::Draw()
{

	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�^�C�g����ʂł��B", GetColor(128, 128, 128));
	DrawGraph(0, 0, grHandle, false);
	fade->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		fade->isEndFlag = TRUE;

	}
	if (fade->isNextFlag == TRUE)
	{
		mSceneChanger->ChangeScene(eScene_GamePlay);
		sound->stopSound(0);
		sound->DeleteSound();
		//delete sound;
	}
}
