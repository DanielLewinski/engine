#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "object.h"
#include "timer.h"

class GameObject : public Object
{
public:
	GameObject(SDL_Rect offset, std::string imagePath, Vector newVelocity, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});

	static void SetFPSCounter(FPSCounter& counter);

	void Render();

	SDL_Rect GetBoundingRectangle();

	void Translate(SDL_Point point);
	void Move();
	SDL_Rect Intersection(SDL_Rect boundingRectangle);

private:
	static FPSCounter* fpsCounter;
	Vector velocity; //Pixels per second
};

#endif // GAMEOBJECT_H

