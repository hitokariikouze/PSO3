
#pragma once

#include "Task.h"
#include "ISceneChanger.h"

class BaseScene : public Task
{

protected:
	int mHandle;
	ISceneChanger* mSceneChanger;
public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene() {}
	virtual void Initialize() override {}
	virtual void Finalize() override;
	virtual void Update() override {}
	virtual void Draw() override;
};