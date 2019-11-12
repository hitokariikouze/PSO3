#include "SceneManager.h"
#include "Title.h"
#include "GamePlay.h"
#include "SceneManager.h"
#include "Ending.h"

SceneManager::SceneManager() : mNextScene(eScene_None)
{
	mScene = (BaseScene*)new Title(this);
}

void SceneManager::Initialize()
{
	mScene->Initialize();
}

void SceneManager::Finalize()
{
	mScene->Finalize();
}

void SceneManager::Update()
{
	if (mNextScene != eScene_None)
	{
		mScene->Finalize();
		delete mScene;
		switch (mNextScene)
		{
		case eScene_Title:
			mScene = (BaseScene*) new Title(this);
			break;
		case eScene_GamePlay:
			mScene = (BaseScene*) new GamePlay(this);
			break;
		case eScene_Ending:
			mScene = (BaseScene*) new Ending(this);
			break;
		}
		mNextScene = eScene_None;
		mScene->Initialize();
	}

	mScene->Update();
}

void SceneManager::Draw()
{
	mScene->Draw();
}

void SceneManager::ChangeScene(eScene NextScene)
{
	mNextScene = NextScene;
}