#ifndef BUTTON_H
#define BUTTON_H

#include "uiobject.h"
#include <functional>

class Button : public UIObject
{
public:
	Button(SDL_Rect offset, std::string imagePath, std::string backgroundPath, std::function<void()> newFunction, bool doesColorKey = false, SDL_Color colorKey = {0,0,0,0});
	Button(SDL_Rect offset, Font& font, std::string imageText, std::string backgroundPath, std::function<void()> newFunction, SDL_Color newColor = {0,0,0,0});
	~Button();

	virtual void EventLoop(SDL_Event &event);

	void Render() override;

protected:
	bool isPointedAt();

	std::function<void()> Function;

	bool wasClicked;

private:
	void LoadBackground(std::string backgroundPath);

	SDL_Texture* background;
};

#endif // BUTTON_H

