#include "sounds.h"

Sound::Sound(std::string soundPath)
{
	try
	{
		sound = Mix_LoadWAV(soundPath.c_str());
		if(sound == nullptr)
			SDLException::throwException();
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}

Sound::~Sound()
{
	Mix_FreeChunk(sound);
}

void Sound::Play(int loops)
{
	Mix_PlayChannel(-1, sound, loops);
}

Music::Music(std::string musicPath)
{
	try
	{
		music = Mix_LoadMUS(musicPath.c_str());
		if(music == nullptr)
			SDLException::throwException();
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

void Music::Play(int loops)
{
	if(Mix_PlayingMusic())
	{
		if(Mix_PausedMusic())
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
	else
		Mix_PlayMusic(music, loops);
}

void Music::Stop()
{
	Mix_HaltMusic();
}
