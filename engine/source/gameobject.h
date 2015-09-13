#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "exceptions.h"

class GameObject
{
public:
	GameObject(SDL_Rect newPosition, std::string imagePath);
	~GameObject();
	SDL_Texture* GetTexture();
	SDL_Rect& GetPosition();
	static void SetRenderer(SDL_Renderer* renderer);

private:
	void LoadSurface(std::string imagePath);
	void LoadTexture(SDL_Surface* surface);

	SDL_Texture* texture;
	SDL_Rect position;

	static SDL_Renderer* renderer;
};

#endif // GAMEOBJECT

