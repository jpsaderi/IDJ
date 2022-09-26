#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#define INCLUDE_SDL_MIXER

#include "GameObject.hpp"
#include "SDL_include.h"
#include <string>

using namespace std;

class GameObject;
class Component{
private:
public:
    Component(GameObject& associated);
    virtual ~Component();
    
    void virtual Start() = 0;
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;
    void virtual NotifyCollision(GameObject& other) = 0;

protected:
    GameObject& associated;
};

#endif