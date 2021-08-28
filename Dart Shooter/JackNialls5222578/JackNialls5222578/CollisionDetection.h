#pragma once
#include<SDL.h>
#include<SDL_image.h>

class CollisionDetection
{
public:
	static bool CheckCollision(SDL_Rect* A, SDL_Rect* B);
};

