#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "SDL_include.h"

class Camera{
private:
    static GameObject* focus;
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;
};

#endif