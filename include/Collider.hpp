#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "GameObject.hpp"
#include "Collision.hpp"

class Collider : public Component{
private:
    Vec2 scale;
    Vec2 offset;

public:    
    Collider(GameObject &associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});
    Rect box;

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    bool IsColliding(Collider other);
};

#endif