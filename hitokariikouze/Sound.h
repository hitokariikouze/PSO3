#pragma once

class Sound
{
public:
	Sound();

	//Sound(int soundFile);

	int soundHandle[5];

	~Sound();

	void playSound(int sH, int pT, int tPF);

	void stopSound(int sH);

	bool CheckSound(int sH);

	void DeleteSound();

	/*void Update();

	bool CheckSound(int);*/

private:

};
