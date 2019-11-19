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
	//ŽžŠÔ‚ð•`‰æ‚µ‚Ü‚·
	DrawFormatString(0, 0, 0x000000, "%d:%02d:%02d", minute, second, comma);   
}

void Timer::Update()
{
	Count();
}

void Timer::Count()
{
	comma = (GetNowCount() - startTime) / 10; 

	second = comma / 100;  //•b‚É•ÏŠ·
	comma %= 60;

	minute = second / 60;  //•ª‚É•ÏŠ·
	second %= 60;
}

