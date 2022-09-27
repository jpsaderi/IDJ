#ifndef STAGESTATE_HPP
#define STAGESTATE_HPP

#define N_ALLIENS 3
#define INCLUDE_SDL

#include "SDL_include.h"
#include "Music.hpp"
#include "State.hpp"
#include "TileMap.hpp"

using namespace std;

class StageState : public State {
private:
    TileSet* tileSet;
    Music* backgroundMusic;
public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif