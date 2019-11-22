#include "Blur.h"

BlurScreen::BlurScreen() {
	blurFlag = false;
}

//�u���[�X�N���[���̍쐬
void BlurScreen::InitBlurScreen(BlurScreen *blur, int alpha,
	int offsetX1, int offsetY1, int offsetX2, int offsetY2)
{
	if (!blur) return; // �u���[�łȂ����return

	int depth; //��ʂ̃J���[�r�b�g�[�x��ۑ�����int�^�ϐ�

	//���݂̉�ʂ̑傫���ƃJ���[�r�b�g���𓾂�i�����͂��ꂼ��̃A�h���X�j
	GetScreenState(&blur->screenWidth, &blur->screenHeight, &depth);

	//�`��Ώۂɂł���O���t�B�b�N���쐬���Ascreen�z��Ɋi�[
	for (int n = 0; n < 2; ++n)
		blur->screen[n] = MakeScreen(blur->screenWidth, blur->screenHeight);
	blur->current = 0;
	blur->alpha = alpha;
	blur->offsetX1 = offsetX1;
	blur->offsetX2 = offsetX2;
	blur->offsetY1 = offsetY1;
	blur->offsetY2 = offsetY2;
}

//�u���[�X�N���[���̍폜
void BlurScreen::DestroyBlurScreen(BlurScreen *blur)
{
	if (!blur) return;
	for (int n = 0; n < 2; ++n)
		DeleteGraph(blur->screen[n]);
}

//MakeScreen�ō쐬�����O���t�B�b�N�n���h���ɕ`�揈�������鏀��
void BlurScreen::PreRenderBlurScreen(BlurScreen *blur)
{
	if (!blur) return;

	SetDrawScreen(blur->screen[blur->current]);
	// ��ʂ�������
	ClearDrawScreen();
}

//���ۂ̕`�揈��
void BlurScreen::PostRenderBlurScreen(BlurScreen *blur)
{
	if (!blur) return;

	int drawMode = GetDrawMode(); //�`�惂�[�h��ۑ�
	SetDrawMode(DX_DRAWMODE_BILINEAR); //�`�惂�[�h���Z�b�g����

	int brendMode, blendParam;
	GetDrawBlendMode(&brendMode, &blendParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blur->alpha); //�u�����h���[�h���Z�b�g����

	//�������ɓǂ݂��񂾃O���t�B�b�N�̊g��k���`��
	DrawExtendGraph(
		blur->offsetX1, blur->offsetY1,
		blur->screenWidth + blur->offsetX2,
		blur->screenHeight + blur->offsetY2,
		blur->screen[1 - blur->current], FALSE);

	//�`��A�u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(brendMode, blendParam);
	SetDrawMode(drawMode);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, blur->screen[blur->current], FALSE);
	blur->current = 1 - blur->current;
}

BlurScreen::~BlurScreen()
{	}