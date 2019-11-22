#pragma once
#include "Player.h"
#include "BaseScene.h"
#include "Stage.h"
#include "Blur.h"
class Player;
class Stage;
class BlurScreen;

class GamePlay : public BaseScene
{
private :
	Player* player;
	Stage* stage;
	BlurScreen* blur;
public:
	GamePlay(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;

};
