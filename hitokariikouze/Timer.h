#pragma once
#include "DxLib.h"

class Timer
{
public:
	Timer();
	void Initialize();
	void Render();
	void Update();
	void Count();
private:
	int minute, second, comma;
	int startTime;
};