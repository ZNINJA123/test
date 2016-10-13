#include"Music.h"

CMusic::CMusic()
{
}

CMusic::~CMusic()
{
	for (int i = 0; i < tracks.size(); i++)
	{
		delete tracks[i];
	}

	for (int i = 0; i < FX.size(); i++)
	{
		delete FX[i];
		delete sfxbuffers[i];
	}
}

int CMusic::CreateMusic(string filename)
{

	int index = tracks.size();
	Music* track = new Music();
	if(!track->openFromFile(filename))

	{
		return -1;
	}

	tracks.push_back(track);
	return index;
}

int CMusic::CreateSFX(string filename)
{
	int index = FX.size();
	Sound* newfx = new Sound();
	SoundBuffer* newBuffer = new SoundBuffer();

	newBuffer->loadFromFile(filename);
	newfx->setBuffer(*newBuffer);


	FX.push_back(newfx);
	sfxbuffers.push_back(newBuffer);


	return index;
}
void CMusic::PlaySFX(int sfx)
{
	FX[sfx]->play();
}

void CMusic::StopSFX(int sfx)
{
	FX[sfx]->stop();
}

void CMusic::PlayMusic(int track,bool loop)
{
	tracks[track]->setLoop(loop);
	tracks[track]->play();

}

void CMusic::StopMusic(int track)
{
	tracks[track]->stop();
}

bool CMusic::isPlaying(int track)
{
	return tracks[track]->Playing;
}