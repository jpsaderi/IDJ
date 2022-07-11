#ifndef FACE_HPP
#define FACE_HPP

#include "SDL_include.h"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <string>

class Face : public Component{
private:
   int hitpoints;
public:
    Face(GameObject& associated);
    
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif