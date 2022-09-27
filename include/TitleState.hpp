#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.hpp"
#include "Text.hpp"

class TitleState : public State {
private:
    
public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif