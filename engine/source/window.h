#ifndef WINDOW_H
#define WINDOW_H

#include "button.h"
#include "sounds.h"
#include "timer.h"

#define SDL_FLAGS SDL_INIT_VIDEO | SDL_INIT_AUDIO
#define IMAGE_FLAGS IMG_INIT_PNG
#define MIXER_FLAGS MIX_INIT_OGG

class Window
{
public:
	Window(unsigned int newWidth, unsigned int newHeight, std::string title = "");
	Window(unsigned int newWidth, unsigned int newHeight, std::vector<SDL_Rect> viewports, std::string title = "");
	~Window();
	void GameLoop();

	void ClearScreen();
	void UpdateScreen();

	void SetViewports(std::vector<SDL_Rect> newViewports);
	void SetActiveViewport(SDL_Rect viewport);

private:
	void InitializeSDL();
	void InitializeIMG() const;
	void InitializeTTF();
	void InitializeMixer();
	void CreateWindow(std::string title);
	void CreateRenderer();

	int width;
	int height;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* windowSurface;
	SDL_Event event;

	std::vector<SDL_Rect> viewports;

};

#endif // WINDOW_H

