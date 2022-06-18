#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "State.hpp"
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
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};

#endif