#pragma once
#include "BaseScene.h"
#include "Timer.h"
#include "Fade.h"
#include "Sound.h"

class Title : public BaseScene
{
private:
	Fade * fade;
public:
	Title(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

	int grHandle;
	Sound* sound;

};