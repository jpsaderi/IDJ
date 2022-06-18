#include "../include/Sprite.hpp"
#include "../include/Game.hpp"

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(string file){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){
    if (IsOpen()){
       SDL_DestroyTexture(texture); 
    //    texture = nullptr; 
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr){
        cout << IMG_GetError() << endl;
    }
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0){
        cout << SDL_GetError() << endl;
    }
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    if(IsOpen() == true){
        if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect) != 0){
            cout << SDL_GetError() << endl;
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