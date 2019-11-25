#include "DxLib.h"
#include "Sound.h"


Sound::Sound()
{
	soundHandle[0] = LoadSoundMem("Sound/MusMus-BGM-012.mp3");
	soundHandle[1] = LoadSoundMem("Sound/White_Lovers_FreeBGM_ver.mp3");
	soundHandle[2] = LoadSoundMem("Sound/Tr6.mp3");

	soundHandle[3] = LoadSoundMem("Sound/car-sudden-braking1.mp3");
	soundHandle[4] = LoadSoundMem("Sound/magic_elevator.mp3");
	soundHandle[5] = LoadSoundMem("Sound/hyun1.mp3");
}

Sound::~Sound()
{

}

void Sound::playSound(int sH, int pT, int tPF)
{
	PlaySoundMem(soundHandle[sH], pT, tPF);
}

void Sound::stopSound(int sH)
{
	StopSoundMem(soundHandle[sH]);
}

bool Sound::CheckSound(int sH)
{
	if (CheckSoundMem(soundHandle[sH]) == 1)
		return true;
	else
		return false;
}

void Sound::DeleteSound()
{
	for (int i = 0; i < 6; i++)
	{
		DeleteSoundMem(soundHandle[i]);
	}
}
