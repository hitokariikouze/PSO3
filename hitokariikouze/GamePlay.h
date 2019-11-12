#pragma once
#include "Player.h"
#include "BaseScene.h"
class Player;


class GamePlay : public BaseScene
{
private :
	Player* player;
public:
	GamePlay(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};
