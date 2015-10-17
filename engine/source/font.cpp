#include "font.h"

Font::Font(std::string fontPath, int size)
{
	try
	{
		font = TTF_OpenFont(fontPath.c_str(), size);
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
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
