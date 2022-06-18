#include "../include/State.hpp"

State::State(){
    quitRequested = false;
    LoadAssets();
}

void State::LoadAssets(){
    bg = *new Sprite("./assets/img/ocean.jpg");
    music = *new Music("./assets/audio/stageState.ogg");
    music.Volume(10);
    music.Play();
}

void State::Update(float dt){
    if (SDL_QuitRequested() == true){
        music.Stop();
        quitRequested = true;
    }
}

void State::Render(){
    bg.Render(0,0);
}

bool State::QuitRequested(){
    return quitRequested;
}