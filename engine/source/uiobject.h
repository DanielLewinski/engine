#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "gameobject.h"

class UIObject : public GameObject
{
public:
	UIObject(SDL_Rect newPosition, std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});
	UIObject(SDL_Rect newPosition, Font& newFont, std::string textureText, SDL_Color newColor = {0,0,0,0});

protected:
	SDL_Texture* LoadTextTexture(std::string textureText, SDL_Color color);

	Font* font;
	SDL_Color color;

};

#endif // UIOBJECT_H

