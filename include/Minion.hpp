#ifndef MINION_HPP
#define MINION_HPP

#include "SDL_include.h"
#include "Component.hpp"
#include <string>
#include "Bullet.hpp"

using namespace std;

class Minion : public Component{
private:
    weak_ptr<GameObject> alienCenter;
    float arc;
    
public:
    Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Shoot(Vec2 target);
    
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif