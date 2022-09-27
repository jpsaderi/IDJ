#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "SDL_include.h"
#include "Component.hpp"
#include "Rect.hpp"
#include "bits/stdc++.h"
#include <string>

using namespace std;

class Component;
class GameObject{
private:
    vector <unique_ptr<Component>> components;
    bool isDead;
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void NotifyCollision(GameObject& other);
    
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);

    Rect box;

    bool started;
    double angleDeg;
};




#endif