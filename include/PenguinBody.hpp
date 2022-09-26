#ifndef PENGUINBODY_HPP
#define PENGINBODY_HPP

#include "SDL_include.h"
#include "GameObject.hpp"
#include "Sprite.hpp"
// #include "State.hpp"
#include "Collider.hpp"
#include "PenguinCannon.hpp"

class PenguinBody : public Component{
private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

public:    
    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);

    static PenguinBody* player;
    Rect GetPosition();
};

#endif