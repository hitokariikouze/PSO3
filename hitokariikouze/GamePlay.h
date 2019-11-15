#pragma once
#include "Player.h"
#include "BaseScene.h"
#include "Stage.h"
class Player;
class Stage;


class GamePlay : public BaseScene
{
private :
	Player* player;
	Stage* stage;
public:
	GamePlay(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};
