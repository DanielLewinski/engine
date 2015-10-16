#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <exception>
#include <SDL2/SDL.h>
#include <string>
#include <stdio.h>

class SDLException: public std::exception
{
public:
	const char* what() const throw();
	static void throwException();
};

class GenericException: public std::exception
{
public:
	GenericException(std::string message);
	const char* what() const throw();

private:
	std::string message;
};

#endif // EXCEPTIONS

