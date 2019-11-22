<<<<<<< HEAD
=======
#pragma once
>>>>>>> origin/sakai
#include "DxLib.h"

//スクリーンをブラーさせるクラス
class BlurScreen
{
public:
	int screen[2];
	int current;
	int alpha;
	int screenWidth, screenHeight;
	int offsetX1, offsetX2, offsetY1, offsetY2;

<<<<<<< HEAD
	bool blurFlag;

	BlurScreen();
=======
	BlurScreen();
	static bool blurFlag;
>>>>>>> origin/sakai

	void InitBlurScreen(BlurScreen *blur, int alpha,
		int offsetX1, int offsetY1, int offsetX2, int offsetY2);

	void DestroyBlurScreen(BlurScreen *blur);

	void PreRenderBlurScreen(BlurScreen *blur);

	void PostRenderBlurScreen(BlurScreen *blur);

	~BlurScreen();
};
