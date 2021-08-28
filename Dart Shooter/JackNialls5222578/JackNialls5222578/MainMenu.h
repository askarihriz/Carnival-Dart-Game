#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"Background.h"

class MainMenu
{
private:
	bool isClicked;
	bool isHover;
	Mix_Chunk* Hover;
	Mix_Chunk* Button;
	Background menuBackground;
public:
	MainMenu();
	~MainMenu();
	void Initialize(SDL_Renderer* ren);
	int EventHandling(SDL_Event& e);
	void Render(SDL_Renderer* ren);
	bool getClicked();
};