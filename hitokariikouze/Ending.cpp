#include "Ending.h"
#include "DxLib.h"
#include "number.h"
#include "Sound.h"

Ending::Ending(ISceneChanger * changer) : BaseScene(changer)
{
	timer = new Timer();
	sound = new Sound();
	sound->playSound(2, DX_PLAYTYPE_LOOP, TRUE);
}

void Ending::Initialize()
{
	grHandle = LoadGraph("Tex/PS03_ending.png");
}

void Ending::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
		sound->stopSound(2);
		//delete sound;
		sound->DeleteSound();
	}
	/*timer->TimeKeep();*/


}

void Ending::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "�G���f�B���O��ʂł��B", GetColor(128, 128, 128));
	DrawGraph(0, 0, grHandle, false);
	timer->rank();
}