#include "window.h"

Window::Window(unsigned int newWidth, unsigned int newHeight, std::string title)
	: width(newWidth), height(newHeight)
{
	try
	{
		InitializeSDL();
		InitializeIMG();
		InitializeTTF();
		InitializeMixer();
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
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::InitializeSDL()
{
	if(SDL_Init(SDL_FLAGS) == -1)
		SDLException::throwException();
}

void Window::InitializeIMG() const
{
	if( (IMG_Init(IMAGE_FLAGS)&IMAGE_FLAGS) != IMAGE_FLAGS)
		SDLException::throwException();
}

void Window::InitializeTTF()
{
	if(TTF_Init() == -1)
		SDLException::throwException();
}

void Window::InitializeMixer()
{
	if((Mix_Init(MIXER_FLAGS)&MIXER_FLAGS) != MIXER_FLAGS)
		SDLException::throwException();

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
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
	Font font("font.ttf", 100);
	Sound sound("sound.wav");
	Music music("music.ogg");
	Timer timer({0,0,100,100}, font);
	FPSCounter fpsCounter({540,0,100,100}, font);
	Button button({0,0,width/2,height/2},font, "Play/Pause", "background.png", [&music, &timer](){ printf("chuj\n"); music.PlayPause(); timer.PlayPause();});
	Button button1({width/2,0,width/2,height/2},font, "Hide Button", "background.png", [&button](){ printf("dupa\n"); button.Activate();});
	Button button2({0,height/2,width/2,height/2},font, "Play sound", "background.png", [&sound](){ printf("kurwa\n"); sound.Play();});
	Button button3({width/2,height/2,width/2,height/2},font, "Stop Music", "background.png", [&music, &timer](){ printf("cipa"); music.Stop(); timer.Stop();});
	//gameObject.ModulateTextureColor(128,128,128);
	//gameObject.ModulateTextureAlpha(128);
	//gameObject.LoadClips({{0,0,64,205},{64,0,64,205},{128,0,64,205},{192,0,64,205}});

	std::cout << sizeof(std::stringstream) << "\n";
	std::cout << sizeof(Window) << "\n" << sizeof(GameObject) << "\n" << sizeof(UIObject) << "\n" << sizeof(Button) << "\n" << sizeof(Timer) << "\n" << sizeof(FPSCounter) << "\n" << sizeof(Font) << "\n" << sizeof(Sound) << "\n" << sizeof(Music) << "\n";

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
		timer.Actualize();
		fpsCounter.Actualize();

		ClearScreen();
		button.Render();
		button1.Render();
		button2.Render();
		button3.Render();
		timer.Render();
		fpsCounter.Render();
		UpdateScreen();
	}
}
