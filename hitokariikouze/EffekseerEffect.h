#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"

using namespace std;

class EffectEf
{
public:
	EffectEf();

	//�G�t�F�N�g�̍��W
	float position_x;
	float position_y;
	float position_z;

	bool acceleratorFlag; //�u�[�X�g�G�t�F�N�g���o���t���O

	//�Đ�����G�t�F�N�g������ϐ�
	int playingEffectHandle[3];

	//�G�t�F�N�g�i�[�p�z��
	int effectMap[3];

	//�G�t�F�N�g�̓ǂݍ���
	void LoadEffect();

	//�G�t�F�N�g�̐���
	int Instantiate(int arNum);

	//�G�t�F�N�g�̒�~
	int StopEffect(int arNum);
	//�X�V
	void Update();
	//�{�^���̉����ꂽ�u�Ԃ��v��
	int OnEffectPush();
	//������Ă邩��ۑ�����ϐ�
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

