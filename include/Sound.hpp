#ifndef SOUND_HPP
#define SOUND_HPP

#include "SDL_include.h"
#include "GameObject.hpp"
#include "Component.hpp"
#include <string>

using namespace std;

class Sound : public Component{
private:
    Mix_Chunk* chunk;
    int channel;
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(string type); //Pai bool

    void Volume(int volume);
};

#endif