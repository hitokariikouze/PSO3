#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger * changer) : mHandle(0)
{
	mSceneChanger = changer;
}

void BaseScene::Finalize()
{
	DeleteGraph(mHandle);
}

void BaseScene::Draw()
{
	DrawGraph(0, 0, mHandle, FALSE);
}