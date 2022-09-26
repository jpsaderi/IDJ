#ifndef BULLET_HPP
#define BULLET_HPP

#include "Component.hpp"
#include "SDL_include.h"
#include "Collider.hpp"
#include <string>

using namespace std;

class Bullet : public Component{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
public:
    bool targetsPlayer;
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, bool targetsPlayer);
    int GetDamage();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);
};

#endif