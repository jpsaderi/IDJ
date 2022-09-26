#include "../include/Camera.hpp"
#include "bits/stdc++.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    InputManager instance = InputManager::GetInstance();
    speed = Vec2(0,0);
    int speed_ = 256;

    if(focus == nullptr){
        if(instance.IsKeyDown(UP_ARROW_KEY)){
            speed += Vec2(0, -1);
        }
        else if(instance.IsKeyDown(DOWN_ARROW_KEY)){
            speed += Vec2(0, 1);
        }
        if(instance.IsKeyDown(LEFT_ARROW_KEY)){
            speed += Vec2(-1, 0);
        }
        else if(instance.IsKeyDown(RIGHT_ARROW_KEY)){
            speed += Vec2(1, 0);
        }
        pos += speed.Normalized()*speed_*dt;
    }
    else{
        pos.x = focus -> box.GetCenter().x-512; //metade largura
        pos.y = focus -> box.GetCenter().y-300; //metade altura
    }
}
