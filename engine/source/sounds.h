#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include "exceptions.h"

class Sound
{
public:
	Sound(std::string soundPath);
	~Sound();
	void Play(int loops = 0);

private:
	Mix_Chunk* sound;
};

class Music
{
public:
	Music(std::string musicPath);
	~Music();
	void PlayPause(int loops = -1);
	void Stop();
	void Restart(int loops = -1);

private:
	Mix_Music* music;
};

#endif // SOUNDS_H

