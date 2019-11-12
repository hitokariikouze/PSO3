#include "Ending.h"
#include "DxLib.h"

Ending::Ending(ISceneChanger * changer) : BaseScene(changer)
{
}

void Ending::Initialize()
{
}

void Ending::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
}

void Ending::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�G���f�B���O��ʂł��B", GetColor(128, 128, 128));
}