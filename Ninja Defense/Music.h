#pragma once
#include <vector>
#include<SFML\Audio.hpp>
#include <string>
using std::string;
using std::vector;
using sf::Music;
using sf::Sound;
using sf::SoundBuffer;

class  CMusic
{
public:
	static CMusic& Getinstance()
	{
		static CMusic Instance;
		return Instance;
	}
	
	vector<Music*> tracks;
	vector<Sound*> FX;
	vector<SoundBuffer*> sfxbuffers;
	~CMusic();

	int CreateMusic(string filename);
	int CreateSFX(string filename);
	void PlaySFX(int sfx);
	void StopSFX(int sfx);
	void PlayMusic(int track, bool loop = true);
	void StopMusic(int track);
	bool isPlaying(int track);

private:
	CMusic();


};