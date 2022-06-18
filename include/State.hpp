#ifndef STATE_HPP
#define STATE_HPP
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Sprite.hpp"
#include "Music.hpp"

using namespace std;

class State{
private:
    Sprite bg;
    Music music;
    bool quitRequested;
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};

#endif