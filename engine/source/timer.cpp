#include "timer.h"

Timer::Timer(SDL_Rect newPosition, Font& newFont, SDL_Color color)
	: UIObject(newPosition, newFont, "0", color), startTime(0), pauseTime(0), isStarted(false), isPaused(false)
{

}

Uint32 Timer::GetTime()
{
	Uint32 time = 0;
	if(isStarted)
	{
		if(isPaused)
			time = pauseTime;
		else
			time = SDL_GetTicks() - startTime;
	}
	return time/1000;
}

void Timer::Actualize()
{
	if(isStarted && !isPaused)
	{
		timeText.str("");
		timeText << GetTime();

		texture = LoadTextTexture(timeText.str().c_str(), color);
	}
}

void Timer::PlayPause()
{
	if(!isStarted)
	{
		isStarted = true;
		startTime = SDL_GetTicks();
	}
	else
	{
		if(isPaused)
		{
			startTime = SDL_GetTicks() - pauseTime;
			pauseTime = 0;
		}
		else
		{
			pauseTime = SDL_GetTicks() - startTime;
			startTime = 0;
		}
		isPaused = !isPaused;
	}
}

void Timer::Stop(std::string defaultText)
{
	if(isStarted)
	{
		startTime = 0;
		pauseTime = 0;

		texture = LoadTextTexture(defaultText.c_str(), color);

		isStarted = false;
		isPaused = false;
	}
}

void Timer::Restart(std::string defaultText)
{
	Stop(defaultText);
	PlayPause();
}

FPSCounter::FPSCounter(SDL_Rect newPosition, Font &newFont, SDL_Color newColor)
	: Timer(newPosition, newFont, newColor), framesCounter(0)
{
	PlayPause();
}

void FPSCounter::Actualize()
{
		++framesCounter;

		if(GetTime() > 0)
		{
			timeText.str("");
			timeText << framesCounter;

			framesCounter = 0;
			Restart(timeText.str());
		}
}
