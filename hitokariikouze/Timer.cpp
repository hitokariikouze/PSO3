#include "Timer.h"

Timer::Timer()
{
}

void Timer::Initialize()
{
	startTime = GetNowCount();
}

void Timer::Render()
{
	//時間を描画します
	DrawFormatString(0, 0, 0x000000, "%d:%02d:%02d", minute, second, comma);   
}

void Timer::Update()
{
	Count();
}

void Timer::Count()
{
	comma = (GetNowCount() - startTime) / 10; 

	second = comma / 100;  //秒に変換
	comma %= 60;

	minute = second / 60;  //分に変換
	second %= 60;
}

