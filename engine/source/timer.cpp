#include "timer.h"

Timer::Timer(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color color)
	: GameObject(newPosition, newFont, textureText, color), startTime(SDL_GetTicks())
{
	timeText.str("");
}

Uint32 Timer::GetTime()
{
	return SDL_GetTicks() - startTime;
}

void Timer::Actualize()
{
	timeText.str("");
	timeText << GetTime()/1000;

	texture = LoadTextTexture(timeText.str().c_str(), color);
}
