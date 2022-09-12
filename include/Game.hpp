#ifndef GAME_HPP
#define GAME_HPP

#include "State.hpp"
#include "SDL_include.h"
#include <string>
#include <bits/stdc++.h> //Faz diferença usar a <iostream>?
using namespace std;

class Game{
private:
    Game(string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime();
};

#endif