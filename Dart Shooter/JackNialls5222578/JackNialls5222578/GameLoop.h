#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"TextureManager.h"
#include"Background.h"
#include"MainMenu.h"
#include"Balloons.h"
#include"CollisionDetection.h"
#include"TextManager.h"
#include<cstdlib>


class GameLoop
{
private:
	SDL_Event evnt;
	const int HEIGHT = 768;
	const int WIDTH = 1024;
	int points = 0;
	int time = 0;
	int counter = 0;
	int ammo = 35;
	bool GameState;
	bool isHover1;
	bool isHover2;
	Mix_Music* Music;
	Mix_Chunk* Point;
	Mix_Chunk* Hit;
	Mix_Chunk* Button;
	Mix_Chunk* Hover;
	Mix_Chunk* ArrowShot;
	Mix_Chunk* BalloonPop;
	MainMenu menu;
	Background background;
	Background restartMenu;
	Background aim;
	Background hand;
	Balloon b1;
	Balloon b2;
	Balloon b3;
	Balloon b4;
	Balloon b5;
	TextManager score;
	TextManager yourScore;
	TextManager timeleft;
	TextManager ammoCount;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;
public:
	GameLoop();
	void MainMenu();
	void LowerMusic();
	bool getGameState();
	void Update();
	void Reset();
	int Restart();
	void Intialize();
	void Event();
	void Render();
	void Clear();
};

