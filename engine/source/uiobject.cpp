#include "uiobject.h"

UIObject::UIObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey, SDL_Color colorKey)
	: GameObject(newPosition, imagePath, doesColorKey, colorKey)
{

}

UIObject::UIObject(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color newColor)
	: GameObject(newPosition), font(&newFont), color(newColor)
{
	texture = LoadTextTexture(textureText, newColor);
}

SDL_Texture* UIObject::LoadTextTexture(std::string textureText, SDL_Color color)
{
	try
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font->Get(), textureText.c_str(), color);
		if(textSurface == nullptr)
			SDLException::throwException();

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(texture == nullptr)
		{
			SDL_FreeSurface(textSurface);
			SDLException::throwException();
		}

		SDL_FreeSurface(textSurface);
		return texture;
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}
