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
	//���Ԃ�`�悵�܂�
	DrawFormatString(0, 0, 0x000000, "%d:%02d:%02d", minute, second, comma);   
}

void Timer::Update()
{
	Count();
}

void Timer::Count()
{
	comma = (GetNowCount() - startTime) / 10; 

	second = comma / 100;  //�b�ɕϊ�
	comma %= 60;

	minute = second / 60;  //���ɕϊ�
	second %= 60;
}

