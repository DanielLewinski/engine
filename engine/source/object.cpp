#include "object.h"

SDL_Renderer* Object::renderer = nullptr;

Object::Object(SDL_Rect offset, std::string imagePath, bool doesColorKey, SDL_Color colorKey)
	: activeClip(nullptr), position({static_cast<double>(offset.x),static_cast<double>(offset.y)}), offsetRect(offset), isActive(true)
{
	texture = LoadSurface(imagePath, doesColorKey, colorKey);
}

Object::Object(SDL_Rect offset)
	: activeClip(nullptr), position({ static_cast<double>(offset.x),static_cast<double>(offset.y) }), offsetRect(offset), isActive(true)
{

}

Object::~Object()
{
	SDL_DestroyTexture(texture);
}

void Object::Activate()
{
	isActive = !isActive;
}

inline void Object::Render()
{
	if(isActive)
	{
		SDL_RenderCopy(renderer, texture, activeClip, &offsetRect);
	}
}

SDL_Texture* Object::LoadSurface(std::string imagePath, bool doesColorKey, SDL_Color colorKey)
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

SDL_Texture* Object::LoadTexture(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == nullptr)
		SDLException::throwException();

	SDL_FreeSurface(surface);
	return texture;

}

void Object::LoadClips(std::vector<SDL_Rect> newClips)
{
	spriteClips = newClips;
}

void Object::SetActiveClip(unsigned int clipIndex)
{
	if(clipIndex < spriteClips.size())
		activeClip = &spriteClips[clipIndex];
}

void Object::SetRenderer(SDL_Renderer *renderer)
{
	Object::renderer = renderer;
}

void Object::ModulateTextureColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

void Object::ModulateTextureAlpha(Uint8 alpha, SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture,blendMode);
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Object::Animate()
{
	static unsigned int frame = 0; //TODO: change this to something sensible
	SetActiveClip(frame);
	++frame %= spriteClips.size();
}
