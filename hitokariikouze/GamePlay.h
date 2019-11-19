#pragma once
#include "Player.h"
#include "BaseScene.h"
#include "Stage.h"
#include "Timer.h"
class Player;
class Stage;
class Timer;


class GamePlay : public BaseScene
{
private :
	Player* player;
	Stage* stage;
	Timer* timer;
public:
	GamePlay(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};
