#include "gameobject.h"

SDL_Renderer* GameObject::renderer = nullptr;

GameObject::GameObject(SDL_Rect newPosition, std::string imagePath)
	: position(newPosition)
{
	try
	{
		LoadSurface(imagePath);
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(texture);
}

void GameObject::LoadSurface(std::string imagePath)
{
	SDL_Surface* surface;
	surface = IMG_Load(imagePath.c_str());
	if(surface == nullptr)
		SDLException::throwException();
	LoadTexture(surface);
}

void GameObject::LoadTexture(SDL_Surface* surface)
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == nullptr)
		SDLException::throwException();
	SDL_FreeSurface(surface);
}

void GameObject::SetRenderer(SDL_Renderer *renderer)
{
	GameObject::renderer = renderer;
}

SDL_Texture* GameObject::GetTexture()
{
	return texture;
}

SDL_Rect& GameObject::GetPosition()
{
	return position;
}
