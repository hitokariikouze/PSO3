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
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "タイトル画面です。", GetColor(128, 128, 128));
}
