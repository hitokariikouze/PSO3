#pragma once

#include "BaseScene.h"

class Ending : public BaseScene
{
public:
	Ending(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};
