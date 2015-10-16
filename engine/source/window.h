#ifndef WINDOW_H
#define WINDOW_H

#include "button.h"

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
	void InitializeIMG(int flags) const;
	void InitializeTTF();
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

