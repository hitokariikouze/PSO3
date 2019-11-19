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
	VECTOR stgPos,srPos1,srPos2;
	int StageHandle,DashHit;
	float sr1, sr2;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	MV1_COLL_RESULT_POLY_DIM HitPlayerDim;
};
