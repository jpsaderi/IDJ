
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include <iostream>
Sprite::Sprite (GameObject &associated) : Component(associated){
    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
}
    
Sprite::Sprite (GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated){
    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
    Open(file);
    SetFrameCount(frameCount);
    SetFrameTime(frameTime);
    this -> secondsToSelfDestruct = secondsToSelfDestruct;
    if(secondsToSelfDestruct > 0)
        selfDestructCount = new Timer();
    else
        selfDestructCount = nullptr;
}
Sprite::~Sprite (){
}
void Sprite::Open (string file){
    if(!IsOpen()){
        texture =  Resources::GetImage(file);
        if(texture == nullptr){
            cout << IMG_GetError()  << endl;
        }
        if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) != 0)
            cout << SDL_GetError() << endl;
        SetClip(0,0,width,height);
        associated.box.w = width;
        associated.box.h = height;

    }
}
void Sprite::SetClip (int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}
void Sprite::Render (){
    Render(associated.box.x-Camera::pos.x,associated.box.y-Camera::pos.y);
}
void Sprite::Render (float x, float y){
    SDL_Rect dsrect;

    dsrect.x = x+clipRect.w/2 - clipRect.w/2*scale.x;
    dsrect.y = y+clipRect.h/2 - clipRect.h/2*scale.y;
    dsrect.w = clipRect.w*scale.x;
    dsrect.h = clipRect.h*scale.y;
    if(IsOpen())
        if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture.get(),&clipRect,&dsrect,associated.angleDeg,nullptr,SDL_FLIP_NONE) != 0)
            cout << SDL_GetError() << endl;
}
using namespace std;
int Sprite::GetWidth (){
    return (width/frameCount)*scale.x;
}
int Sprite::GetHeight (){
    return height*scale.y;
}
bool Sprite::IsOpen (){
    if(texture != nullptr)
        return true;
    return false;
}
void Sprite::Update(float dt){
    timeElapsed += dt;
    if(selfDestructCount != nullptr){
        selfDestructCount ->Update(dt);
        if(selfDestructCount -> Get()>= secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }
    if(timeElapsed >= frameTime){
        if(currentFrame+1 == frameCount){
            SetFrame(0);
        }
        else{
            SetFrame(currentFrame+1);
        }
    }

}
bool Sprite::Is(string type){
    if(type == "Sprite")
        return true;
    return false;
}
Vec2 Sprite::GetScale(){
    return scale;
}
void Sprite::SetScale(float scaleX, float scaleY){
    scale.x = scaleX == 0 ? scale.x : scaleX;
    scale.y = scaleY == 0 ? scale.y : scaleY;
}
void Sprite::Start(){
    
}
void Sprite::SetFrame (int frame){
    currentFrame = frame;
    timeElapsed = 0;
    SetClip(GetWidth()*currentFrame/scale.x,0,width/frameCount,height);
    
}
void Sprite::SetFrameCount (int frameCount){
    this -> frameCount = frameCount;
    SetFrame(0);
    associated.box.w = GetWidth();

}
void Sprite::SetFrameTime (float frameTime){
    this -> frameTime = frameTime;
    timeElapsed = 0;
}
void Sprite::NotifyCollision(GameObject& other){

}