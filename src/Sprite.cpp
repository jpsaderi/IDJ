#include "../include/Sprite.hpp"
#include "../include/Game.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated){
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){
    if (IsOpen()){
    //    SDL_DestroyTexture(texture); 
       texture = nullptr; 
    }
    else{
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr){
            
            cout << "Sprite" << IMG_GetError() << endl;
        }
        if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0){
            cout << "Sprite" <<  SDL_GetError() << endl;
        }
        SetClip(0, 0, width, height);
        associated.box.w = width;
        associated.box.h = height;
    }
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(){
    SDL_Rect dstrect;
    dstrect.x = associated.box.x;
    dstrect.y = associated.box.y;
    dstrect.w = associated.box.w;
    dstrect.h = associated.box.h;

    if(IsOpen()){
        if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect) != 0){
            cout << SDL_GetError() << ':' << texture << endl;
        }
    }
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    if(texture == nullptr){
        return false;
    }
    return true;
}

bool Sprite::Is(string type){
    return type == "Sprite";
}

void Sprite::Update(float dt){

}