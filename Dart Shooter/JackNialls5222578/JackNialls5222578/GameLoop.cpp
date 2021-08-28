#include "GameLoop.h"

GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;
	GameState = true;
	points = 0;
	ammo = 40;
}

bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::Intialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("Dart Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			GameState = true;
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
			Music = Mix_LoadMUS("Sound/backTheme.mp3");
			Point = Mix_LoadWAV("Sound/point1.wav");
			BalloonPop = Mix_LoadWAV("Sound/BalloonPop.wav");
			Hit = Mix_LoadWAV("Sound/hit1.wav");
			Hover = Mix_LoadWAV("Sound/Hover.wav");
			Button = Mix_LoadWAV("Sound/button1.wav");
			ArrowShot = Mix_LoadWAV("Sound/arrow.mp3");
			Mix_PlayMusic(Music, -1);
			Mix_VolumeMusic(10);
			Mix_VolumeChunk(Point, 64);
			Mix_VolumeChunk(Hit, 64);
			Mix_VolumeChunk(ArrowShot, 64);
			Mix_VolumeChunk(BalloonPop, 100);
			background.CreateTexture("Images/backGnd.png", renderer);
			b1.CreateTexture("Images/RedBalloon.png", renderer);
			b1.Initialize();
			b2.CreateTexture("Images/BlueBalloon.png", renderer);
			b2.Initialize();
			b3.CreateTexture("Images/YellowBalloon.png", renderer);
			b3.Initialize();
			b4.CreateTexture("Images/GreenBalloon.png", renderer);
			b4.Initialize();
			b5.CreateTexture("Images/OrangeBalloon.png", renderer);
			b5.Initialize();
			aim.CreateTexture("Images/aim.png", renderer);
			hand.CreateTexture("Images/hand.png", renderer);
			score.CreateFont("Font/calibrib.ttf", 38);
			timeleft.CreateFont("Font/calibrib.ttf", 38);
			yourScore.CreateFont("Font/calibrib.ttf", 50);
			ammoCount.CreateFont("Font/calibrib.ttf", 38);
			restartMenu.CreateTexture("Images/Re.png", renderer);

			std::string s;
			s = "Score: " + std::to_string(points);
			score.Text(s, 255, 255, 255, renderer);

			std::string s2;
			s2 = "Darts: " + std::to_string(ammo);
			ammoCount.Text(s2, 255, 255, 255, renderer);

			std::string s1;
			s1 = "Time: " + std::to_string(abs(time - 40));
			timeleft.Text(s1, 255, 255, 255, renderer);
		}
		else
		{
			std::cout << "Not created!" << std::endl;
		}
	}
	else
	{
		std::cout << "window not created!" << std::endl;
	}
}

void GameLoop::LowerMusic() {
	Mix_VolumeMusic(4);
}

void GameLoop::Reset() {
	GameState = true;
	points = 0;
	time = 0;
	ammo = 35;

	std::string s;
	s = "Score: " + std::to_string(points);
	score.Text(s, 255, 255, 255, renderer);

	std::string s1;
	s1 = "Time: " + std::to_string(abs(time - 40));
	timeleft.Text(s1, 255, 255, 255, renderer);

	std::string s2;
	s2 = "Darts: " + std::to_string(ammo);
	ammoCount.Text(s2, 255, 255, 255, renderer);
}

int GameLoop::Restart() {
	SDL_RenderClear(renderer);
	restartMenu.Render(renderer);
	SDL_RenderPresent(renderer);
	while (true) {
		while (SDL_PollEvent(&evnt)) {
			if (evnt.type == SDL_QUIT)
			{
				return -1;
			}
			if (evnt.type == SDL_MOUSEBUTTONDOWN && evnt.motion.x > 362 && evnt.motion.x < 665 && evnt.motion.y > 300 && evnt.motion.y < 382)
			{
				Mix_PlayChannel(-1, Button, 0);
				while (Mix_Playing(-1))
				{

				}
				return 1;
			}
			if (evnt.motion.x > 362 && evnt.motion.x < 665 && evnt.motion.y > 300 && evnt.motion.y < 382) {
				if (isHover1) {
					Mix_PlayChannel(-1, Hover, 0);
					isHover1 = false;
				}
			}
			else {
				isHover1 = true;
			}
			if (evnt.type == SDL_MOUSEBUTTONDOWN && evnt.motion.x > 362 && evnt.motion.x < 665 && evnt.motion.y > 404 && evnt.motion.y < 490)
			{
				Mix_PlayChannel(-1, Button, 0);
				while (Mix_Playing(-1))
				{

				}
				return -1;
			}
			if (evnt.motion.x > 362 && evnt.motion.x < 665 && evnt.motion.y > 404 && evnt.motion.y < 490) {
				if (isHover2) {
					Mix_PlayChannel(-1, Hover, 0);
					isHover2 = false;
				}
			}
			else {
				isHover2 = true;
			}
		}
	}
}

void GameLoop::MainMenu()
{
	menu.Initialize(renderer);
	while (!menu.getClicked())
	{
		if (menu.EventHandling(event1) == -1)
		{
			GameState = false;
			break;
		}
		SDL_RenderClear(renderer);
		menu.Render(renderer);
		SDL_RenderPresent(renderer);
	}
}

void GameLoop::Event()
{
	while (SDL_PollEvent(&evnt)) {

		if (evnt.type == SDL_QUIT) {
			GameState = false;
		}
		if (evnt.type == SDL_MOUSEBUTTONDOWN) {
			ammo--;
			std::string s2;
			s2 = "Darts: " + std::to_string(ammo);
			ammoCount.Text(s2, 255, 255, 255, renderer);

			Mix_PlayChannel(-1, ArrowShot, 0);
			SDL_Rect temp;
			temp.h = 2;
			temp.w = 2;
			temp.x = evnt.motion.x - 1;
			temp.y = evnt.motion.y - 1;
			if (CollisionDetection::CheckCollision(&b1.getDest(), &temp)) {
				if (b1.getState()) {
					b1.Die();
					points++;
					// Scoring Mechanics
					std::string s;
					s = "Score: " + std::to_string(points);
					score.Text(s, 255, 255, 255, renderer);
					Mix_PlayChannel(-1, Point, 0);
					Mix_PlayChannel(-1, BalloonPop, 0);
				}
			}
			if (CollisionDetection::CheckCollision(&b2.getDest(), &temp)) {
				if (b2.getState()) {
					b2.Die();
					points++;
					// Scoring Mechanics
					std::string s;
					s = "Score: " + std::to_string(points);
					score.Text(s, 255, 255, 255, renderer);
					Mix_PlayChannel(-1, Point, 0);
					Mix_PlayChannel(-1, BalloonPop, 0);
				}
			}
			if (CollisionDetection::CheckCollision(&b3.getDest(), &temp)) {
				if (b3.getState()) {
					b3.Die();
					points++;
					// Scoring Mechanics
					std::string s;
					s = "Score: " + std::to_string(points);
					score.Text(s, 255, 255, 255, renderer);
					Mix_PlayChannel(-1, Point, 0);
					Mix_PlayChannel(-1, BalloonPop, 0);
				}
			}
			if (CollisionDetection::CheckCollision(&b4.getDest(), &temp)) {
				if (b4.getState()) {
					b4.Die();
					points++;
					// Scoring Mechanics
					std::string s;
					s = "Score: " + std::to_string(points);
					score.Text(s, 255, 255, 255, renderer);
					Mix_PlayChannel(-1, Point, 0);
					Mix_PlayChannel(-1, BalloonPop, 0);
				}
			}
			if (CollisionDetection::CheckCollision(&b5.getDest(), &temp)) {
				if (b5.getState()) {
					b5.Die();
					points++;
					// Scoring Mechanics
					std::string s;
					s = "Score: " + std::to_string(points);
					score.Text(s, 255, 255, 255, renderer);
					Mix_PlayChannel(-1, Point, 0);
					Mix_PlayChannel(-1, BalloonPop, 0);
				}
			}
		}
		aim.AimUpdate(evnt.motion.x, evnt.motion.y);
		hand.GunUpdate(evnt.motion.x);
	}
}

void GameLoop::Update()
{
	b1.Update();
	b2.Update();
	b3.Update();
	b4.Update();
	b5.Update();


	if (abs(time - 40) == 0 || ammo == -1) {
		std::string s1;
		s1 = "Time: " + std::to_string(abs(time - 40));
		timeleft.Text(s1, 255, 255, 255, renderer);

		std::string s2;
		s2 = "Darts: " + std::to_string(ammo);
		ammoCount.Text(s2, 255, 255, 255, renderer);

		std::string s3;
		s3 = "You Popped " + std::to_string(points) + " Balloons !";
		yourScore.Text(s3, 255, 255, 255, renderer);
		yourScore.Render(renderer, 280, 330);
		SDL_RenderPresent(renderer);
		SDL_Delay(3000);

		yourScore.FreeTexture();
		GameState = false;
	}

	if (counter % 100 == 0) {
		time++;
		std::string s1;
		s1 = "Time: " + std::to_string(abs(time - 40));
		timeleft.Text(s1, 255, 255, 255, renderer);
	}

	counter++;
}

void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	background.Render(renderer);
	b1.Render(renderer);
	b2.Render(renderer);
	b3.Render(renderer);
	b4.Render(renderer);
	b5.Render(renderer);
	aim.AimRender(renderer);
	hand.GunRender(renderer);
	score.Render(renderer, 875, 10);
	timeleft.Render(renderer, 10, 10);
	ammoCount.Render(renderer, 10, 720);
	SDL_RenderPresent(renderer);
}

void GameLoop::Clear()
{
	yourScore.CloseFont();
	score.CloseFont();
	timeleft.CloseFont();
	ammoCount.CloseFont();
	Mix_FreeChunk(Point);
	Mix_FreeChunk(Hit);
	Mix_FreeChunk(ArrowShot);
	Mix_FreeMusic(Music);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}