#include "Timer.h"
#include "DxLib.h"
#include "number.h"
#include "Player.h"

int Timer::oldtime;
Timer::Timer()
{
	player = new Player();
	
}

Timer::~Timer()
{
	delete player;
}

void Timer::Initialize()
{
	StartTime = GetNowCount();
 	hour = 0;  minute = 0; 
	ranking[RANKING_MAX] = { 0 };
	drawcount = 3; count = 0;
	timeFlag = FALSE;
}

void Timer::Update()
{
	second = (GetNowCount() - StartTime) / 1000;  

	minute = second / 60;  
	second %= 60;

	hour = minute / 60;  
	minute %= 60;

	//ClearDrawScreen();    

	DrawFormatString(0, 40, GetColor(128, 128, 128), "%d:%02d:%02d", hour, minute, second);
	DrawFormatString(0, 60, GetColor(128, 128, 128), "%d",second);
}

void Timer::ranking_sort(float score)
{
	int i;
	int j;
	for (i = 0; i<RANKING_MAX; i++) {
									 
		if (score>ranking[i]) {
			for (j = RANKING_MAX - 1; j>i; j--) {
				ranking[j] = ranking[j - 1];
			}
			ranking[i] = score;
			break;
		}

	}
}

void Timer::result()
{
	ranking_sort(second);
}

void Timer::rank()
{
	

	minute = oldtime / 60;
	oldtime %= 60;

	hour = minute / 60;
	minute %= 60;
	DrawFormatString(0, 100, GetColor(128, 128, 128), "%d:%02d:%02d", hour, minute, oldtime);
	DrawFormatString(0, 80, GetColor(128, 128, 128), "%d",oldtime);
}

void Timer::TimeKeep()
{
	oldtime = second;
}

void Timer::CountUpdate()
{
	count++;
	SetFontSize(30);
	SetFontThickness(3);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	if (count >= 60 && drawcount >= 0)
	{
		drawcount--;
		count = 0;
	}
	if (drawcount > 0)
	{
		DrawFormatString(400, 150, GetColor(128, 128, 128), "%d", drawcount);
	}
	if (drawcount == 0)
	{
		DrawString(400, 150, "GOÅI", GetColor(128, 128, 128));
	}
	if (drawcount == -1)
	{
		timeFlag = TRUE;
	}
}


