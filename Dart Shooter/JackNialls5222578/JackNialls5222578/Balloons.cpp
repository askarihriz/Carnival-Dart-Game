#include "Balloons.h"
#include<iostream>

void Balloon::Initialize() {
	//setSrc(360, 120, 35, 115);
	//Quack = Mix_LoadWAV("Sound/duck.wav");
	//Mix_VolumeChunk(Quack, 34);
}

void Balloon::Clear() {
	//Mix_FreeChunk(Quack);
}

void Balloon::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), NULL, &getDest());
}

void Balloon::Update()
{
	if (isAlive) {
		setDest(DestX, DestY += 3, 60, 40);
	}
	if (DestY > 550 || !isAlive) {
		isAlive = true;
		DestY = rand() % 300 - 768;
		DestX = rand() % 980;
	}
}

bool Balloon::getState() {
	return isAlive;
}

void Balloon::Die() {
	isAlive = false;
}
