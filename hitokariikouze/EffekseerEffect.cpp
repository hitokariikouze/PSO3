#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerEffect.h"

EffectEf::EffectEf() {
	LoadEffect();

	// �G�t�F�N�g�̕\������ʒu��ݒ肷��B
	position_x = 0.0f; position_y = 0.0f; position_z = 0.0f;

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	for (int i = 0; i < 3; i++) {
		playingEffectHandle[i] = -1;
	}

	acceleratorFlag = false;

	inputFrame = 0; // ���͎�t

	scaleTimer = 0;

	accelTimer = 0;

	instanceFlag = false;

	fireFlag = false;
}

//�G�t�F�N�g��ǂݍ���
void EffectEf::LoadEffect()
{
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	effectMap[0] = LoadEffekseerEffect("Effect/warpFire.efk");
	effectMap[1] = LoadEffekseerEffect("Effect/backFire.efk");
	effectMap[2] = LoadEffekseerEffect("Effect/warpAcccel.efk");
}

//�G�t�F�N�g�̐����i�����̓f�B�N�V���i���̃L�[�j
int EffectEf::Instantiate(int arNum)
{
	playingEffectHandle[arNum] = PlayEffekseer3DEffect(effectMap[arNum]);
	return playingEffectHandle[arNum];
}

//�X�V����
void EffectEf::Update()
{
	// �L�[���͂��X�V
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

//�����ꂽ�u�Ԃ����
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


//�G�t�F�N�g�̒�~����
int EffectEf::StopEffect(int arNum)
{
	playingEffectHandle[arNum] = StopEffekseer3DEffect(effectMap[arNum]);
	return playingEffectHandle[arNum];
}

//�G�t�F�N�g�̍��W�𓯊�
int EffectEf::SetEffectPosition(int arNum, int x, int y, int z)
{
	return SetPosPlayingEffekseer3DEffect(playingEffectHandle[arNum], x, y, z);
}

//�G�t�F�N�g�̌����𓯊�
int EffectEf::SetEffectRotation(int arNum, float angle)
{
	return SetRotationPlayingEffekseer3DEffect(playingEffectHandle[arNum], 0, angle, 0);
}

//�G�t�F�N�g�̃T�C�Y��ύX
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
