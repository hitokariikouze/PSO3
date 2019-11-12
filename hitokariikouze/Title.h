#pragma once
#include "BaseScene.h"

class Title : public BaseScene
{
public:
	Title(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};