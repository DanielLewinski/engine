#include "gameobject.h"

SDL_Renderer* GameObject::renderer = nullptr;

GameObject::GameObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey, Uint8 keyR, Uint8 keyG, Uint8 keyB)
	: position(newPosition), activeClip(nullptr)
{
	try
	{
		LoadSurface(imagePath, doesColorKey, keyR, keyG, keyB);
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

void GameObject::LoadSurface(std::string imagePath, bool doesColorKey, Uint8 keyR, Uint8 keyG, Uint8 keyB)
{
	SDL_Surface* surface;
	surface = IMG_Load(imagePath.c_str());
	if(surface == nullptr)
		SDLException::throwException();
	SDL_SetColorKey(surface, doesColorKey, SDL_MapRGB(surface->format, keyR, keyG, keyB));
	LoadTexture(surface);
}

void GameObject::LoadTexture(SDL_Surface* surface)
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == nullptr)
		SDLException::throwException();
	SDL_FreeSurface(surface);
}

void GameObject::LoadClips(std::vector<SDL_Rect> newClips)
{
	clips = newClips;
}

void GameObject::SetActiveClip(int clipIndex)
{
	if(clipIndex == -1)
		activeClip = nullptr;
	else if(static_cast<unsigned int>(clipIndex) < clips.size())
		activeClip = &clips[clipIndex];
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

SDL_Texture* GameObject::GetTexture()
{
	return texture;
}

SDL_Rect& GameObject::GetPosition()
{
	return position;
}

SDL_Rect* GameObject::GetClip()
{
	return activeClip;
}
