#include "window.h"

Window::Window(unsigned int newWidth, unsigned int newHeight, std::string title)
	: width(newWidth), height(newHeight)
{
	try
	{
		InitializeSDL();
		InitializeIMG(IMG_INIT_PNG);
		InitializeTTF();
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

Window::Window(unsigned int newWidth, unsigned int newHeight, std::vector<SDL_Rect> viewports, std::string title)
	: Window(newWidth, newHeight, title)
{
	SetViewports(viewports);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::InitializeSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		SDLException::throwException();
}

void Window::InitializeIMG(int flags) const
{
	if( (IMG_Init(flags)&flags) != flags)
		SDLException::throwException();
}

void Window::InitializeTTF()
{
	if(TTF_Init() == -1)
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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr)
		SDLException::throwException();
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	GameObject::SetRenderer(renderer);
}

inline void Window::ClearScreen()
{
	SDL_RenderClear(renderer);
}

inline void Window::UpdateScreen()
{
	SDL_RenderPresent(renderer);
}

inline void Window::SetViewports(std::vector<SDL_Rect> newViewports)
{
	if(!newViewports.empty())
	{
		viewports = newViewports;
		SetActiveViewport(viewports[0]);
	}
}

inline void Window::SetActiveViewport(SDL_Rect viewport)
{
	SDL_RenderSetViewport(renderer, &viewport);
}

void Window::GameLoop()
{
	bool done = false;
	//GameObject button({0,0,64,205}, "foo.png",true, 0, 255, 255);
	Font font("font.ttf", 250);

	Button button({0,0,width/2,height/2},font, "Chuj!!!", "background.png", [](){ printf("chuj\n");});
	Button button1({width/2,0,width/2,height/2},font, "Dupa!!!", "background.png", [&button](){ printf("dupa\n"); button.Activate();});
	Button button2({0,height/2,width/2,height/2},font, "Kurwa!!!", "background.png", [](){ printf("kurwa\n");});
	Button button3({width/2,height/2,width/2,height/2},font, "Cipa!!!", "background.png", [](){ printf("cipa");});
	//gameObject.ModulateTextureColor(128,128,128);
	//gameObject.ModulateTextureAlpha(128);
	//gameObject.LoadClips({{0,0,64,205},{64,0,64,205},{128,0,64,205},{192,0,64,205}});

	while(!done)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				done = true;
			button.EventLoop(event);
			button1.EventLoop(event);
			button2.EventLoop(event);
			button3.EventLoop(event);
		}
		//gameObject.Animate();

		ClearScreen();
		button.Render();
		button1.Render();
		button2.Render();
		button3.Render();
		UpdateScreen();
	}
}
