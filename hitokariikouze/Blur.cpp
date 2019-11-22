#include "Blur.h"

BlurScreen::BlurScreen() {
	blurFlag = false;
}

//ブラースクリーンの作成
void BlurScreen::InitBlurScreen(BlurScreen *blur, int alpha,
	int offsetX1, int offsetY1, int offsetX2, int offsetY2)
{
	if (!blur) return; // ブラーでなければreturn

	int depth; //画面のカラービット深度を保存するint型変数

	//現在の画面の大きさとカラービット数を得る（引数はそれぞれのアドレス）
	GetScreenState(&blur->screenWidth, &blur->screenHeight, &depth);

	//描画対象にできるグラフィックを作成し、screen配列に格納
	for (int n = 0; n < 2; ++n)
		blur->screen[n] = MakeScreen(blur->screenWidth, blur->screenHeight);
	blur->current = 0;
	blur->alpha = alpha;
	blur->offsetX1 = offsetX1;
	blur->offsetX2 = offsetX2;
	blur->offsetY1 = offsetY1;
	blur->offsetY2 = offsetY2;
}

//ブラースクリーンの削除
void BlurScreen::DestroyBlurScreen(BlurScreen *blur)
{
	if (!blur) return;
	for (int n = 0; n < 2; ++n)
		DeleteGraph(blur->screen[n]);
}

//MakeScreenで作成したグラフィックハンドルに描画処理をする準備
void BlurScreen::PreRenderBlurScreen(BlurScreen *blur)
{
	if (!blur) return;

	SetDrawScreen(blur->screen[blur->current]);
	// 画面を初期化
	ClearDrawScreen();
}

//実際の描画処理
void BlurScreen::PostRenderBlurScreen(BlurScreen *blur)
{
	if (!blur) return;

	int drawMode = GetDrawMode(); //描画モードを保存
	SetDrawMode(DX_DRAWMODE_BILINEAR); //描画モードをセットする

	int brendMode, blendParam;
	GetDrawBlendMode(&brendMode, &blendParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blur->alpha); //ブレンドモードをセットする

	//メモリに読みこんだグラフィックの拡大縮小描画
	DrawExtendGraph(
		blur->offsetX1, blur->offsetY1,
		blur->screenWidth + blur->offsetX2,
		blur->screenHeight + blur->offsetY2,
		blur->screen[1 - blur->current], FALSE);

	//描画、ブレンドモードを元に戻す
	SetDrawBlendMode(brendMode, blendParam);
	SetDrawMode(drawMode);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, blur->screen[blur->current], FALSE);
	blur->current = 1 - blur->current;
}

BlurScreen::~BlurScreen()
{	}