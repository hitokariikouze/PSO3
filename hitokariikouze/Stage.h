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
	~Stage();
	void Initialize();
	void Render();
	void Update();

private:
	VECTOR stgPos,srPos1,srPos2,srPos3,srPos4,srPos5,srPos6,gaolPos;
	int StageHandle,GoalHit,DashHit,counthandle,DashHandle;
	float sr1, sr2;
	int Shit;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;
	MV1_COLL_RESULT_POLY_DIM HitDashDim;
};
