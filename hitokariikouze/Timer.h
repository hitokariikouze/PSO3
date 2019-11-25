#pragma once
#include "Player.h"

class Timer
{
private:
	Player* player;
public:
	Timer();
	~Timer();

	int StartTime;    //�N�����̎��Ԃ��i�[����ϐ�
	int hour, minute, second;
	int count, drawcount;
	bool timeFlag;
	static int oldtime;
	float ranking[];
	
	

	void Initialize();
	void Update();
	void ranking_sort(float score);
	void result();
	void rank();
	void TimeKeep();
	void CountUpdate();

private:

};

