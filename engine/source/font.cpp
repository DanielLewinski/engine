#include "font.h"

Font::Font(std::string fontPath, int size)
{
	font = TTF_OpenFont(fontPath.c_str(), size);
}

Font::Font()
	: font(nullptr)
{

}

Font::~Font()
{
	TTF_CloseFont(font);
}

TTF_Font* Font::Get()
{
	return font;
}
