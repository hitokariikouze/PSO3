#pragma once
#include "DxLib.h"

//�X�N���[�����u���[������N���X
class BlurScreen
{
public:
	int screen[2];
	int current;
	int alpha;
	int screenWidth, screenHeight;
	int offsetX1, offsetX2, offsetY1, offsetY2;

	BlurScreen();
	static bool blurFlag;

	void InitBlurScreen(BlurScreen *blur, int alpha,
		int offsetX1, int offsetY1, int offsetX2, int offsetY2);

	void DestroyBlurScreen(BlurScreen *blur);

	void PreRenderBlurScreen(BlurScreen *blur);

	void PostRenderBlurScreen(BlurScreen *blur);

	~BlurScreen();
};
