#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"

using namespace std;

class EffectEf
{
public:
	EffectEf();

	//エフェクトの座標
	float position_x;
	float position_y;
	float position_z;

	bool acceleratorFlag; //ブーストエフェクトを出すフラグ

	//再生するエフェクトを入れる変数
	int playingEffectHandle[3];

	//エフェクト格納用配列
	int effectMap[3];

	//エフェクトの読み込み
	void LoadEffect();

	//エフェクトの生成
	int Instantiate(int arNum);

	//エフェクトの停止
	int StopEffect(int arNum);
	//更新
	void Update();
	//ボタンの押された瞬間を計測
	int OnEffectPush();
	//押されてるかを保存する変数
	int inputFrame;

	float scaleTimer;

	float accelTimer;

	bool instanceFlag;

	bool fireFlag;

	int SetEffectPosition(int arNum, int x, int y, int z);

	int SetEffectRotation(int arNum, float angle);

	int SetEffectSize(int arNum, int x, int y, int z);

	bool EffectSet(bool nowAccecl);

	~EffectEf();
};

