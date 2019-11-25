#pragma once

class SlipStream
{
public:
	SlipStream();

	//ƒ‰ƒ“ƒ_ƒ€’l‚ð’è‹`
	int randam360;
	int randam360_2;
	int randam360_3;

	float accelTimer;

	int windowSizeCenterW;
	int windowSizeCenterH;

	int windowPlusW;
	int windowPlusH;

	int st;
	int en;

	float stMinus;

	bool SlipStreamStart(bool slipFlag);
};
