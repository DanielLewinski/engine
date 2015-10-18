#include "timer.h"

Timer::Timer(SDL_Rect offset, Font& newFont, SDL_Color color)
	: UIObject(offset, newFont, "0", color), startTime(0), pauseTime(0), isStarted(false), isPaused(false)
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
	return time;
}

void Timer::Actualize()
{
	if(isStarted && !isPaused)
	{
		timeText.str("");
		timeText << GetTime()/1000;

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

FPSCounter::FPSCounter(SDL_Rect offset, Font &newFont, int newFrameCap, SDL_Color newColor)
	: Timer(offset, newFont, newColor), framesCounter(0), frameCap(newFrameCap), lastFrameTime(0), timeDelta(0)
{
	PlayPause();
}

void FPSCounter::Actualize()
{
	timeDelta = (GetTime() - lastFrameTime)/1000.0;
	lastFrameTime = GetTime();

	if(GetTime()/1000 > 0)
	{
		timeText.str("");
		timeText << framesCounter;

		framesCounter = 0;
		lastFrameTime = 0;
		Restart(timeText.str());
	}
	++framesCounter;

	if(frameCap > 0)
	{
		if(GetTime() < framesCounter*(1000.0/frameCap))
			SDL_Delay(framesCounter*(1000.0/frameCap) - GetTime());
	}
}

double FPSCounter::GetTimeDelta()
{
	return timeDelta;
}
