#include "CollisionDetection.h"

bool CollisionDetection::CheckCollision(SDL_Rect* A, SDL_Rect* B)
{
	SDL_bool Collision = SDL_HasIntersection(A, B);
	if (Collision)
	{
		return true;
	}
	else
		return false;
}