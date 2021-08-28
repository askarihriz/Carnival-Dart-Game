#pragma once
#include"Object.h"

class Background : public Object
{
private:

public:
	void Reset();
	void Render(SDL_Renderer* ren);
	void AimRender(SDL_Renderer* ren);
	void GunRender(SDL_Renderer* ren);
	void AimUpdate(int X, int Y);
	void GunUpdate(int X);
};

