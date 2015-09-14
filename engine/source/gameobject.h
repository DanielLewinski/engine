#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "exceptions.h"
#include <vector>

class GameObject
{
public:
	GameObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey = false, Uint8 keyR = 0, Uint8 keyG = 0, Uint8 keyB = 0);
	~GameObject();

	SDL_Texture* GetTexture();
	SDL_Rect& GetPosition();
	SDL_Rect* GetClip();

	static void SetRenderer(SDL_Renderer* renderer);

	void LoadSurface(std::string imagePath, bool doesColorKey = false, Uint8 keyR = 0, Uint8 keyG = 0, Uint8 keyB = 0);

	void LoadClips(std::vector<SDL_Rect> newClips); //TODO: Adapt this function to handle spritesheet animations
	void SetActiveClip(int clipIndex = -1);

	void ModulateTextureColor(Uint8 r, Uint8 g, Uint8 b);
	void ModulateTextureAlpha(Uint8, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

private:
	void LoadTexture(SDL_Surface* surface);

	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Rect* activeClip;
	std::vector<SDL_Rect> clips;

	static SDL_Renderer* renderer;
};

#endif // GAMEOBJECT

