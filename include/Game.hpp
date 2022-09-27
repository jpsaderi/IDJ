#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include "State.hpp"
#include "StageState.hpp"
#include "TitleState.hpp"
#include <string>
#include <bits/stdc++.h> 

using namespace std;

class Game{
private:
    void CalculateDeltaTime();
    int frameStart;
    float dt;

    static Game* instance;
    
    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    static stack <unique_ptr<State>> stateStack;
public:
    Game(string title, int width, int height);
    ~Game();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    void Push(State* state);
    void Run();
    float GetDeltaTime();
};

#endif