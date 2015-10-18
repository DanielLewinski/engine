#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "object.h"

class UIObject : public Object
{
public:
	UIObject(SDL_Rect offset, std::string imagePath, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});
	UIObject(SDL_Rect offset, Font& newFont, std::string textureText, SDL_Color newColor = {0,0,0,0});

protected:
	SDL_Texture* LoadTextTexture(std::string textureText, SDL_Color color);

	Font* font;
	SDL_Color color;

};

#endif // UIOBJECT_H

