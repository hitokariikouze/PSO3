#include "Stage.h"
#include "DxLib.h"
#include "Player.h"
#include "number.h"

#define DASH_COUNT 2.0f

Stage::Stage(Player* player)
{
	m_player = player;
}

Stage::~Stage()
{
	delete m_player;
}

void Stage::Initialize()
{
	sr1 = 40.0f, sr2 = 40.0f;
	stgPos = VGet(0.0f, 0.0f, 0.0f);

	StageHandle = MV1LoadModel("Tex/New_Course03.mqo");
	DashHandle = MV1LoadModel("Tex/Dash_Bord.mqo");
	counthandle = LoadGraph("tex/Ggo2.png");
	MV1SetScale(StageHandle, VGet(0.5, 0.5, 0.5));
	MV1SetScale(DashHandle, VGet(0.5f, 0.5f, 0.5f));
	MV1SetupCollInfo(StageHandle, -1, 8, 8, 8);
	MV1SetupCollInfo(DashHandle, -1, 8, 8, 8);
	DashHit = 0;
	Shit = 0;

}

void Stage::Render()
{
	srPos1 = VGet(5200.0f, 40.0f, 7500.0f);
	srPos2 = VGet(3100.0f, 40.0f, -650.0f);
	MV1DrawModel(StageHandle);
	MV1DrawModel(DashHandle);
	MV1SetPosition(StageHandle, stgPos);
	MV1SetPosition(DashHandle, stgPos);
	//DrawSphere3D(srPos1, SPHERE_ENUM_SIZE, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawSphere3D(srPos2, SPHERE_ENUM_SIZE, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawGraph(90, 90, counthandle, FALSE);
}

void Stage::Update()
{
	HitPolyDim = MV1CollCheck_Sphere(StageHandle, -1, m_player->GetPosition(), PLAYER_ENUM_DEFAULT_SIZE);
	if (HitPolyDim.HitNum >= 1 && m_player->GetPosition().y <= -15)
	{
		//DrawString(0, 0, "ƒ‚ƒfƒ‹‚É“–‚½‚Á‚½I", GetColor(255, 0, 0));
		m_player->ColFlag = TRUE;
	}
	if (HitPolyDim.HitNum == 0)
	{
		m_player->ColFlag = FALSE;
	}
	GoalHit = HitCheck_Sphere_Sphere(m_player->GetPosition(), SPHERE_ENUM_SIZE, srPos2, sr2);
	if (GoalHit >= 1)
	{
		m_player->isEndFlag = TRUE;
	}
	if (GoalHit == 0)
	{
		m_player->isEndFlag = FALSE;
	}
	HitDashDim = MV1CollCheck_Sphere(DashHandle, -1, m_player->GetPosition(), PLAYER_ENUM_DEFAULT_SIZE);
	if (HitDashDim.HitNum >= 1)
	{
		m_player->dashCount = DASH_COUNT;
	}


	Shit = HitCheck_Sphere_Sphere(m_player->GetPosition(), SPHERE_ENUM_SIZE, srPos1, sr1);
	if (Shit >= 1)
	{
		m_player->Checkcount++;
	}
	//DrawFormatString(0, 0, GetColor(128, 128, 128), "dim   %d", DashHit);
	MV1CollResultPolyDimTerminate(HitPolyDim);
}
