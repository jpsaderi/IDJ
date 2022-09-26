#ifndef PENGINCANNON_HPP
#define PENGINCANNON_HPP

#include "SDL_include.h"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Timer.hpp"
#include "Sound.hpp"
#include "Collider.hpp"
// #include "State.hpp"

using namespace std;

class PenguinCannon : public Component{
private:
    weak_ptr<GameObject> pbody;
    float angle;
    Timer* timer;
public:    
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);
    
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);

    void Shoot();
};

#endif