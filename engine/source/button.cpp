#include "button.h"

Button::Button(SDL_Rect newPosition, std::string imagePath, std::string backgroundPath, std::function<void()> newFunction, bool doesColorKey, SDL_Color colorKey)
	: GameObject(newPosition, imagePath, doesColorKey, colorKey), Function(newFunction), wasClicked(false)
{
	LoadBackground(backgroundPath);
}

Button::Button(SDL_Rect newPosition, Font& font, std::string imageText, std::string backgroundPath, std::function<void()> newFunction, SDL_Color color)
	: GameObject(newPosition, font,imageText, color), Function(newFunction), wasClicked(false)
{
	LoadBackground(backgroundPath.c_str());
}

Button::~Button()
{
	SDL_DestroyTexture(background);
}

void Button::LoadBackground(std::string backgroundPath)
{
	try
	{
		background = LoadSurface(backgroundPath.c_str());
		LoadClips({{0, 0, imageSize.x, imageSize.y/2},{0, imageSize.y/2, imageSize.x, imageSize.y/2}});
		SetActiveClip(0);
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}

void Button::Render()
{
	if(isActive)
	{
		SDL_RenderCopy(renderer, background, activeClip, &position);
		SDL_RenderCopy(renderer, texture, nullptr, &position);
	}
}

bool Button::isPointedAt()
{
	SDL_Point mousePosition;
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

	if(mousePosition.x > position.x + position.w || mousePosition.x < position.x || mousePosition.y >  position.y + position.h || mousePosition.y < position.y)
		return false;

	return true;
}

void Button::EventLoop(SDL_Event& event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && isPointedAt() && isActive)
	{
		SetActiveClip(1);
		wasClicked = true;
	}
	if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		SetActiveClip(0);
		if(isPointedAt() && wasClicked)
			Function();
		wasClicked = false;
	}

}
