#ifndef STATE_HPP
#define STATE_HPP
#define INCLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Bits/stdc++.h"
#include <memory>
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "Face.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include <math.h>
#include "TileMap.hpp"
#include "CameraFollower.hpp"

using namespace std;

class State{
private:
    Music music;
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    vector <unique_ptr<GameObject>> objectArray;
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};

#endif