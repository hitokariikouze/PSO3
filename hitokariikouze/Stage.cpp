#include "Stage.h"
#include "DxLib.h"
#include "Player.h"
#include "number.h"

Stage::Stage(Player* player)
{
	m_player = player;
}

void Stage::Initialize()
{
	sr1 = 200.0f, sr2 = 40.0f;
	stgPos = VGet(0.0f, 0.0f, 0.0f);
	StageHandle = MV1LoadModel("Tex/Race_Course_Small.mqo");
	MV1SetScale(StageHandle, VGet(5.0f, 2.0f, 5.0f));
	MV1SetupCollInfo(StageHandle, -1, 8, 8, 8);
	DashHit = 0;
}

void Stage::Render()
{
	srPos1 = VGet(1100.0f, 40.0f, 300.0f);
	srPos2 = VGet(-1000.0f, 40.0f, 500.0f);
	MV1DrawModel(StageHandle);
	MV1SetPosition(StageHandle, stgPos);
	DrawSphere3D(srPos1, sr1, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	DrawSphere3D(srPos2, sr2, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void Stage::Update()
{
	 HitPolyDim = MV1CollCheck_Sphere(StageHandle, -1,m_player->GetPosition(), PLAYER_ENUM_DEFAULT_SIZE );
	if (HitPolyDim.HitNum >= 1)
	{
		/*DrawString(0, 0, "ƒ‚ƒfƒ‹‚É“–‚½‚Á‚½I", GetColor(255, 0, 0));*/
  		m_player->ColFlag = TRUE;	
	}
	if (HitPolyDim.HitNum == 0)
	{
		m_player->ColFlag = FALSE;
	}
	DashHit =  HitCheck_Sphere_Sphere(m_player->GetPosition(), PLAYER_ENUM_DEFAULT_SIZE, srPos1, sr1);
	if (DashHit >= 1)
	{
		m_player->DashFlag = 1;
	}
	if (DashHit == 0)
	{
		m_player->DashFlag = 0;
	}
	/*DrawFormatString(0, 0, GetColor(128, 128, 128), "dim   %d", DashHit);*/
	MV1CollResultPolyDimTerminate(HitPolyDim);
}
