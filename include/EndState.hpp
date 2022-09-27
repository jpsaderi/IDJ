#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "GameData.hpp"
#include "InputManager.hpp"
#include "Music.hpp"
#include "State.hpp"	
#include "Text.hpp"

class EndState : public State{
private:
    Music *backgroundMusic;
public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif