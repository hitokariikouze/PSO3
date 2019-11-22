#pragma once
#include "Player.h"
#include "BaseScene.h"
#include "Stage.h"
#include "Blur.h"
#include "Camera.h"
#include "SlipStream.h"
#include "EffekseerEffect.h"

class Player;
class Stage;
class BlurScreen;

class GamePlay : public BaseScene
{
private:
	Player* player;
	Stage* stage;

	Camera* camera;
	BlurScreen* blur;
	SlipStream* slip;
	EffectEf* effekseer;

public:
	GamePlay(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;


};
