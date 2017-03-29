#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class SoundObject
{

private	:
	SoundObject()
		{

		}

public:
	static bool bInstanceFlag;
	static SoundObject *soundObject;
	static SoundObject* getInstance();

	void loadSounds();

	vector<SoundBuffer> m_vBufferInterfaceSounds;
	vector<Sound> m_vInterfaceSounds;


	~SoundObject()
	{
		bInstanceFlag = false;
	}

};
#endif WINDOW_H