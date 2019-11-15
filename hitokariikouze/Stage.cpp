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
	
	stgPos = VGet(0.0f, 0.0f, 0.0f);
	StageHandle = MV1LoadModel("Tex/Race_Course_Small.mqo");
	MV1SetScale(StageHandle, VGet(5.0f, 2.0f, 5.0f));
	MV1SetupCollInfo(StageHandle, -1, 8, 8, 8);
}

void Stage::Render()
{
	MV1DrawModel(StageHandle);
	MV1SetPosition(StageHandle, stgPos);
}

void Stage::Update()
{
	 HitPolyDim = MV1CollCheck_Sphere(StageHandle, -1,m_player->GetPosition()/*VAdd( m_player->GetPosition(),VGet(0.0f,-20.0f,5.0f))*/, PLAYER_ENUM_DEFAULT_SIZE /2);
	if (HitPolyDim.HitNum >= 1)
	{
		/*DrawString(0, 0, "ƒ‚ƒfƒ‹‚É“–‚½‚Á‚½I", GetColor(255, 0, 0));*/
  		m_player->ColFlag = TRUE;
		for (int i = 0; i < HitPolyDim.HitNum; i++)
		{
			//// “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚ð•`‰æ
			//DrawTriangle3D(
			//	HitPolyDim.Dim[i].Position[0],
			//	HitPolyDim.Dim[i].Position[1],
			//	HitPolyDim.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
		}
		DrawFormatString(0, 0, GetColor(128, 128, 128), "Hit Poly Num   %d", HitPolyDim.HitNum);
	}
	if (HitPolyDim.HitNum == 0)
	{
		m_player->ColFlag = FALSE;
	}
	
	MV1CollResultPolyDimTerminate(HitPolyDim);
}
