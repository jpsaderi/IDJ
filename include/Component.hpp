#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>
#include "GameObject.hpp"

using namespace std;

class GameObject;
class Component{
private:
public:
    Component(GameObject& associated);
    virtual ~Component();
    
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;

protected:
    GameObject& associated;
};

#endif