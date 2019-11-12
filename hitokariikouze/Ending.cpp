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
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "エンディング画面です。", GetColor(128, 128, 128));
}