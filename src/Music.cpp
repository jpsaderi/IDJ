#include "../include/Music.hpp"

Music::Music(){
    
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
    music = Resources::GetMusic(file).get();
}

bool Music::IsOpen(){
    if(music == nullptr){
        return false;
    }
    return true;
}

Music::~Music(){
    Stop(1500);
}

void Music::Volume(int volume){ // Salvando o nosso ouvido 1...2...3...
    Mix_VolumeMusic(volume);
}