#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger * changer) : BaseScene(changer)
{
}

void Title::Initialize()
{
}

void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		mSceneChanger->ChangeScene(eScene_GamePlay);
	}
}

void Title::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�^�C�g����ʂł��B", GetColor(128, 128, 128));
}
