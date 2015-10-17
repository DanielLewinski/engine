#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "exceptions.h"
#include "font.h"
#include <vector>
#include <SDL2/SDL_image.h>

class GameObject
{
public:
	GameObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});
	GameObject(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color newColor = {0,0,0,0});
	~GameObject();

	virtual void Render();

	static void SetRenderer(SDL_Renderer* renderer);

	SDL_Texture* LoadSurface(std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});

	void LoadClips(std::vector<SDL_Rect> newClips); //TODO: Adapt this function to handle spritesheet animations
	void SetActiveClip(unsigned int clipIndex = -1);
	void Animate();
	void Activate();

	void ModulateTextureColor(Uint8 r, Uint8 g, Uint8 b);
	void ModulateTextureAlpha(Uint8, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

protected:
	SDL_Texture* LoadTexture(SDL_Surface* surface);
	SDL_Texture* LoadTextTexture(std::string textureText, SDL_Color color);

	Font* font;
	SDL_Color color;
	SDL_Texture* texture;
	static SDL_Renderer* renderer;
	SDL_Rect* activeClip;
	SDL_Rect position;
	SDL_Point imageSize;
	bool isActive;

private:
	std::vector<SDL_Rect> spriteClips;

};

#endif // GAMEOBJECT

