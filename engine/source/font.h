#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>
#include <string>

class Font
{
public:
	Font(std::string fontPath, int size);
	Font();
	~Font();
	TTF_Font* Get();
private:
	TTF_Font* font;
};

#endif // FONT_H

