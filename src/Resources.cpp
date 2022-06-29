#include "../include/Resources.hpp"
#include "../include/Game.hpp"

unordered_map<string,SDL_Texture*> Resources::imageTable;
unordered_map<string,Mix_Chunk*> Resources::soundTable;
unordered_map<string,Mix_Music*> Resources::musicTable;

SDL_Texture* Resources::GetImage(string file){
    auto it = imageTable.find(file);
    if(it == imageTable.end()){
        imageTable[file] = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    }
    else{
        return it -> second;
    }
}

void Resources::ClearImages(){
    for(auto i = imageTable.begin(); i != imageTable.end(); i++){
        SDL_DestroyTexture(i -> second);
    }
    // imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file){
    auto it = musicTable.find(file);
    if(it == musicTable.end()){
        musicTable[file] = Mix_LoadMUS(file.c_str());
    }
    else{
        return it -> second;
    }
}

void Resources::ClearMusics(){
    for(auto i = musicTable.begin(); i != musicTable.end(); i++){
        Mix_FreeMusic(i -> second);
    }
    // musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){
    auto it = soundTable.find(file);
    if(it == soundTable.end()){
        soundTable[file] = Mix_LoadWAV(file.c_str());
    }
    else{
        return it -> second;
    }
}

void Resources::ClearSounds(){
    for(auto i = soundTable.begin(); i != soundTable.end(); i++){
        Mix_FreeChunk(i -> second);
    }
    // soundTable.clear();
}