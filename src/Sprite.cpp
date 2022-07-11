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
    // SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){
    if (IsOpen() == false){
        texture = Resources::GetImage(file);
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
    Render(associated.box.x-Camera::pos.x, associated.box.y-Camera::pos.y);
}

void Sprite::Render(float x, float y){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

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