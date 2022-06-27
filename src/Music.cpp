#include "../include/Music.hpp"

Music::Music(){
    // music = nullptr;
}

Music::Music(string file){
    Open(file);
}

void Music::Play(int times){
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
    music = Mix_LoadMUS(file.c_str());
}

bool Music::IsOpen(){
    if(music == nullptr){
        return false;
    }
    return true;
}

Music::~Music(){
    Stop(1500);
    Mix_FreeMusic(music);
}

void Music::Volume(int volume){ // Salvando o nosso ouvido 1...2...3...
    Mix_VolumeMusic(volume);
}