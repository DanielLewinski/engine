#ifndef OBJECT
#define OBJECT

#include "exceptions.h"
#include "font.h"
#include <vector>
#include <SDL2/SDL_image.h>

struct Vector
{
	double x;
	double y;
};

class Object
{
public:
	Object(SDL_Rect offset, std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});
	~Object();

	virtual void Render();

	static void SetRenderer(SDL_Renderer* renderer);

	SDL_Texture* LoadSurface(std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});

	void LoadClips(std::vector<SDL_Rect> newClips); //TODO: Adapt this function to handle spritesheet animations
	void SetActiveClip(unsigned int clipIndex = -1);
	void Animate(); //TODO: Make animations depend on framerate
	void Activate();

	void ModulateTextureColor(Uint8 r, Uint8 g, Uint8 b);
	void ModulateTextureAlpha(Uint8, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

protected:
	Object(SDL_Rect offset);

	SDL_Texture* LoadTexture(SDL_Surface* surface);

	static SDL_Renderer* renderer;

	SDL_Texture* texture;
	SDL_Rect* activeClip;

	Vector position;
	SDL_Rect offsetRect;
	SDL_Point imageSize;

	bool isActive;

private:
	std::vector<SDL_Rect> spriteClips;

};

#endif //OBJECT

