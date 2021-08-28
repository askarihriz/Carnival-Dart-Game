#pragma once
#include "Object.h"
#include<SDL_mixer.h>
#include<iostream>

class Balloon :public Object
{
private:
    int SrcW = 328;
    int DestY = rand() % 300 - 768;
    int DestX = rand() % 990;
    int altDestY = rand() % 300 + 10;
    int altDestX = rand() % 100 + 1024;
    int counter = 0;
    bool isAlive = true;
public:
    void Initialize();
    void Clear();
    void Update();
    bool getState();
    void Die();
    void Render(SDL_Renderer* ren);
};

