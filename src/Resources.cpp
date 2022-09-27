#include "../include/Resources.hpp"
#include "../include/Game.hpp"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file){
    auto it = imageTable.find(file);
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(it == imageTable.end()){
        if(texture == nullptr){
            cout << "Error loading texture: " << file << endl;
            return nullptr;
        }
        else{
            imageTable[file] = shared_ptr<SDL_Texture>(texture, [](SDL_Texture* txtr){SDL_DestroyTexture(txtr);});
            return imageTable[file];
        }
    }
    else{
        return it -> second;
    }
}

shared_ptr<Mix_Music> Resources::GetMusic(string file){
    auto it = musicTable.find(file);
    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if(it == musicTable.end()){
        if(music == nullptr){
            cout << "Error loading music: " << file << endl;
            return nullptr;
        }
        else{
            musicTable[file] = shared_ptr<Mix_Music>(music, [](Mix_Music* msc){Mix_FreeMusic(msc);});
            return musicTable[file];
        }
    }
    else{
        return it -> second;
    }
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file){
    auto it = soundTable.find(file);
    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if(it == soundTable.end()){
        if(sound == nullptr){
            cout << "Error loading sound: " << file << endl;
            return nullptr;
        }
        else{
            soundTable[file] = shared_ptr<Mix_Chunk>(sound, [](Mix_Chunk* snd){Mix_FreeChunk(snd);});
            return soundTable[file];
        }
    }
    else{
        return it -> second;
    }
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize){
    auto it = fontTable.find(file+to_string(fontSize));
    TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
    if(it == fontTable.end()){
        if(font == nullptr){
            cout << "Error loading font: " << file << endl;
            return nullptr;
        }
        else{
            fontTable[file+to_string(fontSize)] = shared_ptr<TTF_Font>(font, [](TTF_Font* fnt){TTF_CloseFont(fnt);});
            return fontTable[file+to_string(fontSize)];
        }
    }
    else{
        return it -> second;
    }
}

void Resources::ClearImages(){
    for(auto i = imageTable.begin(); i != imageTable.end(); i++){
        if(i->second.unique()){
            imageTable.erase(i);
        }
    }
}

void Resources::ClearMusics(){
    for(auto i = musicTable.begin(); i != musicTable.end(); i++){
        if(i->second.unique()){
            musicTable.erase(i);
        }
    }
}

void Resources::ClearSounds(){
    for(auto i = soundTable.begin(); i != soundTable.end(); i++){
        if(i->second.unique()){
            soundTable.erase(i);
        }
    }
}

void Resources::ClearFonts(){
    for(auto i = fontTable.begin(); i != fontTable.end(); i++){
        if(i->second.unique()){
            fontTable.erase(i);
        }
    }
}