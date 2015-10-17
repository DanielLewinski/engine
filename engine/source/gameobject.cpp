#include "gameobject.h"

SDL_Renderer* GameObject::renderer = nullptr;

GameObject::GameObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey, SDL_Color colorKey)
	: activeClip(nullptr), position(newPosition), isActive(true)
{
	texture = LoadSurface(imagePath, doesColorKey, colorKey);
}
/*
GameObject::GameObject(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color newColor)
	: font(&newFont), color(newColor), activeClip(nullptr), position(newPosition), isActive(true)
{
	texture = LoadTextTexture(textureText, newColor);
}
*/
GameObject::GameObject(SDL_Rect newPosition)
	: activeClip(nullptr), position(newPosition), isActive(true)
{

}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
}

void GameObject::Activate()
{
	isActive = !isActive;
}

inline void GameObject::Render()
{
	if(isActive)
		SDL_RenderCopy(renderer, texture, activeClip, &position);
}

SDL_Texture* GameObject::LoadSurface(std::string imagePath, bool doesColorKey, SDL_Color colorKey)
{
	try
	{
		SDL_Surface* surface;
		surface = IMG_Load(imagePath.c_str());
		if(surface == nullptr)
			SDLException::throwException();

		imageSize = {surface->w, surface->h};

		SDL_SetColorKey(surface, doesColorKey, SDL_MapRGB(surface->format, colorKey.r, colorKey.g, colorKey.b));
		LoadClips({{0, 0, surface->w, surface->h}});
		SetActiveClip(0);
		return LoadTexture(surface);
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}

SDL_Texture* GameObject::LoadTexture(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == nullptr)
		SDLException::throwException();

	SDL_FreeSurface(surface);
	return texture;

}
/*
SDL_Texture* GameObject::LoadTextTexture(std::string textureText, SDL_Color color)
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
*/
void GameObject::LoadClips(std::vector<SDL_Rect> newClips)
{
	spriteClips = newClips;
}

void GameObject::SetActiveClip(unsigned int clipIndex)
{
	if(clipIndex < spriteClips.size())
		activeClip = &spriteClips[clipIndex];
}

void GameObject::SetRenderer(SDL_Renderer *renderer)
{
	GameObject::renderer = renderer;
}

void GameObject::ModulateTextureColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

void GameObject::ModulateTextureAlpha(Uint8 alpha, SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture,blendMode);
	SDL_SetTextureAlphaMod(texture, alpha);
}

void GameObject::Animate()
{
	static unsigned int frame = 0; //TODO: change this to something sensible
	SetActiveClip(frame);
	++frame %= spriteClips.size();
}
