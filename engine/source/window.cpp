#include "window.h"

Window::Window(unsigned int newWidth, unsigned int newHeight, std::string title)
	: width(newWidth), height(newHeight)
{
	try
	{
		InitializeSDL();
		InitializeIMG(IMG_INIT_PNG);
		CreateWindow(title);
		CreateRenderer();
	}
	catch(std::exception& exception)
	{
		printf("%s\n", exception.what());
		std::terminate();
	}
	windowSurface = SDL_GetWindowSurface(window);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void Window::InitializeSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		SDLException::throwException();
}

void Window::InitializeIMG(int flags)
{
	if( (IMG_Init(flags)&flags) != flags)
		SDLException::throwException();
}

void Window::CreateWindow(std::string title)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(window == nullptr)
		SDLException::throwException();
}

void Window::CreateRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr)
		SDLException::throwException();
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	GameObject::SetRenderer(renderer);
}

void Window::ShowObject(GameObject& gameObject)
{
	SDL_RenderCopy(renderer, gameObject.GetTexture(), nullptr, nullptr);
}

void Window::GameLoop()
{
	bool terminate = false;
	GameObject gameObject({0,0,320,240}, "loaded.png");

	while(!terminate)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				terminate = true;
		}
		SDL_RenderClear(renderer);
		ShowObject(gameObject);
		SDL_RenderPresent(renderer);
	}
}
