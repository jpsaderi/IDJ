#ifndef CAMERAFOLLOWER_HPP
#define CAMERAFOLLOWER_HPP

#include "Camera.hpp"
#include "Component.hpp"
#include "SDL_include.h"
#include <string>

class CameraFollower : public Component{
private:

public:
    CameraFollower(GameObject& go);
    
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif