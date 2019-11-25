#pragma once

#include "BaseScene.h"
#include "Timer.h"
#include "Sound.h"

class Ending : public BaseScene
{
private:
	Timer * timer;
public:
	Ending(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

	int grHandle;
	Sound* sound;
};
