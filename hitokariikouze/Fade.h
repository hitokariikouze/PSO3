#pragma once

class Fade
{
public:
	Fade();
	~Fade();
	void Initialize();
	void Update();

	float c,d, white;
	bool isEndFlag,isNextFlag;
private:

};
