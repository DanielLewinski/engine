#ifndef TIMER_H
#define TIMER_H

#include "uiobject.h"
#include <sstream>

class Timer : public UIObject
{
public:
	Timer(SDL_Rect newPosition, Font& newFont, SDL_Color color = {0,0,0,0});
	virtual void Actualize();
	Uint32 GetTime();

	void PlayPause();
	void Stop(std::string defaultText = " ");
	void Restart(std::string defaultText = " ");

protected:
	std::stringstream timeText;

private:
	Uint32 startTime;
	Uint32 pauseTime;
	bool isStarted;
	bool isPaused;
};

class FPSCounter : public Timer
{
public:
	FPSCounter(SDL_Rect newPosition, Font& newFont, SDL_Color newColor = {0,0,0,0});
	void Actualize();

private:
	int framesCounter;
};

#endif // TIMER_H
