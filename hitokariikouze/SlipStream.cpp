#define _USE_MATH_DEFINES
#include "DxLib.h"
#include "SlipStream.h"
#include <cmath>
#include <math.h>
#include "number.h"

SlipStream::SlipStream()
{
	randam360 = 0;
	randam360_2 = 0;
	randam360_3 = 0;

	accelTimer = 0;

	windowSizeCenterW = WINDOWWIDTH / 2;
	windowSizeCenterH = WINDOWHEIGHT / 2;

	windowPlusW = 0;
	windowPlusH = 0;

	st = 100;
	en = 350;

	stMinus = 0;

}

bool SlipStream::SlipStreamStart(bool slipFlag) {
	if (slipFlag) {
		accelTimer += 0.1f;
		if (accelTimer >= 0.3f) {
			accelTimer = 0;

			randam360 = GetRand(360) * (M_PI / 180);
			randam360_2 = GetRand(360) * (M_PI / 180);
			randam360_3 = GetRand(360) * (M_PI / 180);
			stMinus = GetRand(st / 2);

		}
		DrawLine(windowSizeCenterW + cos(randam360) * (st + stMinus),
			windowSizeCenterH + sin(randam360) * (st + stMinus),
			windowSizeCenterW + cos(randam360) * en,
			windowSizeCenterH + sin(randam360) * en,
			GetColor(150, 150, 150), 5);

		DrawLine(windowSizeCenterW + cos(randam360_2) * (st + stMinus),
			windowSizeCenterH + sin(randam360_2) * (st + stMinus),
			windowSizeCenterW + cos(randam360_2) * en,
			windowSizeCenterH + sin(randam360_2) * en,
			GetColor(150, 150, 150), 5);

		DrawLine(windowSizeCenterW + cos(randam360_3) * (st + stMinus),
			windowSizeCenterH + sin(randam360_3) * (st + stMinus),
			windowSizeCenterW + cos(randam360_3) * en,
			windowSizeCenterH + sin(randam360_3) * en,
			GetColor(150, 150, 150), 5);

		return slipFlag;
	}
	
}