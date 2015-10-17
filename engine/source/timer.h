#ifndef TIMER_H
#define TIMER_H

#include "gameobject.h"
#include <sstream>

class Timer : public GameObject
{
public:
	Timer(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color color = {0,0,0,0});
	void Actualize();
	Uint32 GetTime();

private:
	Uint32 startTime;
	std::stringstream timeText;
};

#endif // TIMER_H
