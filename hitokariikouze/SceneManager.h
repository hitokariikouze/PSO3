
#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Timer.h"

class SceneManager : public ISceneChanger, Task
{

public:
	SceneManager();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ChangeScene(eScene NextScene) override;

private:
	BaseScene * mScene;
	eScene mNextScene;
	Timer* timer;
};