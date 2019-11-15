#pragma once
#include "DxLib.h"
#include "Player.h"
class Player;

class Stage
{
private:
	Player* m_player;
public:
	Stage(Player* player);
	void Initialize();
	void Render();
	void Update();

private:
	VECTOR stgPos;
	int StageHandle;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
};
