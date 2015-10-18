#include "gameobject.h"

FPSCounter* GameObject::fpsCounter = nullptr;

GameObject::GameObject(SDL_Rect offset, std::string imagePath, Vector newVelocity, bool doesColorKey, SDL_Color colorKey)
	: Object(offset, imagePath, doesColorKey, colorKey), velocity(newVelocity)
{

}

void GameObject::SetFPSCounter(FPSCounter& counter)
{
	fpsCounter = &counter;
}

SDL_Rect GameObject::GetBoundingRectangle()
{
	return offsetRect;
}

void GameObject::Render()
{
	if(isActive)
	{
		offsetRect.x = static_cast<int>(position.x);
		offsetRect.y = static_cast<int>(position.y);
		SDL_RenderCopy(renderer, texture, activeClip, &offsetRect);
	}
}

void GameObject::Translate(SDL_Point point)
{
	position.x = static_cast<double>(point.x);
	position.y = static_cast<double>(point.y);
}

void GameObject::Move()
{
	position.x += velocity.x * fpsCounter->GetTimeDelta();
	position.y += velocity.y * fpsCounter->GetTimeDelta();
}


SDL_Rect GameObject::Intersection(SDL_Rect boundingRectangle)
{
	SDL_Point topLeft = {std::max(offsetRect.x, boundingRectangle.x), std::max(offsetRect.y, boundingRectangle.y) };
	SDL_Point bottomRight = {std::min(offsetRect.x + offsetRect.w, boundingRectangle.x + boundingRectangle.w), std::min(offsetRect.y + offsetRect.h, boundingRectangle.y + boundingRectangle.h) };

	int width = bottomRight.x - topLeft.x;
	int height = bottomRight.y - topLeft.y;
	SDL_Rect intersection;
	if(width > 0 && height > 0)
		intersection = {topLeft.x, topLeft.y, width, height};
	else
		intersection = {0,0,0,0};
	return intersection;
}
