#include "MainMenu.h"

MainMenu::MainMenu()
{
	isClicked = false;
}

void MainMenu::Initialize(SDL_Renderer* ren)
{
	menuBackground.CreateTexture("Images/StartScr.png", ren);
	Hover = Mix_LoadWAV("Sound/Hover.wav");
	Button = Mix_LoadWAV("Sound/button1.wav");
}

int MainMenu::EventHandling(SDL_Event& e)
{
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return -1;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && e.motion.x > 330 && e.motion.x < 690 && e.motion.y > 464 && e.motion.y < 566)
		{
			Mix_PlayChannel(-1, Button, 0);
			while (Mix_Playing(-1))
			{

			}
			isClicked = true;
		}
		if (e.motion.x > 330 && e.motion.x < 690 && e.motion.y > 464 && e.motion.y < 566) {
			if (isHover) {
				Mix_PlayChannel(-1, Hover, 0);
				isHover = false;
			}
		}
		else {
			isHover = true;
		}
		return 0;
	}
}

void MainMenu::Render(SDL_Renderer* ren)
{
	menuBackground.Render(ren);
}

bool MainMenu::getClicked()
{
	return isClicked;
}

MainMenu::~MainMenu()
{
	isClicked = false;
	Mix_FreeChunk(Hover);
	Mix_FreeChunk(Button);
}