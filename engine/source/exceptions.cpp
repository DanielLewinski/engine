#include "exceptions.h"

const char* SDLException::what() const throw()
{
	return SDL_GetError();
}

void SDLException::throwException()
{
	SDLException exception;
	throw exception;
}

const char* GenericException::what() const throw()
{
	return message.c_str();
}

GenericException::GenericException(std::string newMessage)
	: message(newMessage)
{
}
