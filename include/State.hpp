#ifndef STATE_HPP
#define STATE_HPP

#define INCLUDE_SDL

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
#include "Alien.hpp"

using namespace std;

class State{
private:
    Music music;
    bool quitRequested;
    void Input();
    bool started;
    vector <shared_ptr<GameObject>> objectArray;
    
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    weak_ptr<GameObject> AddObject(GameObject* go);
    weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif