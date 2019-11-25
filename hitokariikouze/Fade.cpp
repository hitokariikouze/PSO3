#include "Fade.h"
#include "DxLib.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::Initialize()
{
	c = 0;
	d = 0;
	white = GetColor(255, 255, 255);
	isEndFlag = FALSE;
	isNextFlag = FALSE;
}

void Fade::Update()
{

	if (isEndFlag == TRUE)
	{
		//ClearDrawScreen();
		//if (c >= 0 && c < 256)                    //c��0~256�̎�
		//	SetDrawBright(c, c, c);        //�i�X�����邭(c= 0->255)
		//if (c >= 256 && c < 400)                  //c��256~400�̎�
		//	SetDrawBright(255, 255, 255);  //�ʏ�̖��邳
		//if (c >= 400 && c < 400 + 256)              //c��400~400+256�̎�
		//	SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));

		// 
		//
		//c++;                                //c���J�E���g�A�b�v

		//if (c == 400 + 256)
		//{
		//	isNextFlag  = TRUE;
		//}
		
		if (c > 0)
		{
			c -= 5.0f;
			SetDrawBright(c, c, c);
		}
		if (c == 0)
		{
			d += 5.0f;
			SetDrawBright(d, d, d);
		}
		if (d >= 255)
		{
			isNextFlag = TRUE;
		}
		DrawBox(0, 0, 800, 600, white, TRUE);
	}
}
