#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL_include.h"

class Timer{
private:
    float time;
public:    
    Timer();
    void Update(float dt);
    void Restart();
    float Get();
};

#endif