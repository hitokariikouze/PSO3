#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerEffect.h"

EffectEf::EffectEf() {
	LoadEffect();

	// エフェクトの表示する位置を設定する。
	position_x = 0.0f; position_y = 0.0f; position_z = 0.0f;

	// 再生中のエフェクトのハンドルを初期化する。
	for (int i = 0; i < 3; i++) {
		playingEffectHandle[i] = -1;
	}

	acceleratorFlag = false;

	inputFrame = 0; // 入力受付

	scaleTimer = 0;

	accelTimer = 0;

	instanceFlag = false;

	fireFlag = false;
}

//エフェクトを読み込み
void EffectEf::LoadEffect()
{
	// エフェクトリソースを読み込む。
	effectMap[0] = LoadEffekseerEffect("Effect/warpFire.efk");
	effectMap[1] = LoadEffekseerEffect("Effect/backFire.efk");
	effectMap[2] = LoadEffekseerEffect("Effect/warpAcccel.efk");
}

//エフェクトの生成（引数はディクショナリのキー）
int EffectEf::Instantiate(int arNum)
{
	playingEffectHandle[arNum] = PlayEffekseer3DEffect(effectMap[arNum]);
	return playingEffectHandle[arNum];
}

//更新処理
void EffectEf::Update()
{
	// キー入力を更新
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

//押された瞬間を取る
int EffectEf::OnEffectPush()
{
	if (CheckHitKey(KEY_INPUT_I))
	{
		inputFrame++;
	}
	else
	{
		inputFrame = 0;
	}
	return inputFrame;
}

//


//エフェクトの停止処理
int EffectEf::StopEffect(int arNum)
{
	playingEffectHandle[arNum] = StopEffekseer3DEffect(effectMap[arNum]);
	return playingEffectHandle[arNum];
}

//エフェクトの座標を同期
int EffectEf::SetEffectPosition(int arNum, int x, int y, int z)
{
	return SetPosPlayingEffekseer3DEffect(playingEffectHandle[arNum], x, y, z);
}

//エフェクトの向きを同期
int EffectEf::SetEffectRotation(int arNum, float angle)
{
	return SetRotationPlayingEffekseer3DEffect(playingEffectHandle[arNum], 0, angle, 0);
}

//エフェクトのサイズを変更
int EffectEf::SetEffectSize(int arNum, int x, int y, int z)
{
	return SetScalePlayingEffekseer3DEffect(playingEffectHandle[arNum], x, y, z);
}

bool EffectEf::EffectSet(bool nowAccecl)
{
	if (nowAccecl)
	{
		if (!instanceFlag) {
			playingEffectHandle[1] = PlayEffekseer3DEffect(effectMap[1]);
			playingEffectHandle[2] = PlayEffekseer3DEffect(effectMap[2]);
			instanceFlag = true;
		}
		else
		{
			SetScalePlayingEffekseer3DEffect(playingEffectHandle[1], 0.4, 0.4, 0.4);
			SetScalePlayingEffekseer3DEffect(playingEffectHandle[2], 0.4, 0.4, 0.4);

		}
		if (!fireFlag) {
			playingEffectHandle[0] = PlayEffekseer3DEffect(effectMap[0]);
			fireFlag = true;
		}

	}
	else if (!nowAccecl)
	{
		fireFlag = false;
	}
	return nowAccecl;

}

EffectEf::~EffectEf()
{
	Effkseer_End();
}
