#include "../include/PenguinBody.hpp"
#include "../include/Game.hpp"
#include "bits/stdc++.h"
PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    Sprite* sprite = new Sprite(associated, "assets/img/penguin.png");    
    associated.AddComponent(sprite);
    player = this;
    speed = Vec2(0, 0);
    linearSpeed = 0.1;
    angle = 0;
    hp = 100;
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    State* instance = &Game::GetInstance().GetState();
    GameObject* go = new GameObject();
    weak_ptr<GameObject> penguinCenter = instance->GetObjectPtr(&associated);
    PenguinCannon* penguinCannon = new PenguinCannon(*go, penguinCenter);
    go -> AddComponent(penguinCannon);
    pcannon = instance->AddObject(go);
}

void PenguinBody::Update(float dt){
    Vec2 penguinPos = Vec2(associated.box.x,associated.box.y);
    InputManager instance = InputManager::GetInstance();
    if(instance.IsKeyDown(W_KEY)){
        if(speed.x <= 40)
            speed = speed+Vec2(1,0);
        if(speed.x > 40)
            speed.x = 40;
    }
    else if(instance.IsKeyDown(S_KEY)){
        if(speed.x > 0)
            speed = speed+Vec2(-1,0);
        if(speed.x < 0)
            speed.x = 0;
    }
    else{
        if(speed.x > 0)
            speed = speed-Vec2(linearSpeed,0);
    }
    
    if(instance.IsKeyDown(D_KEY)){
        angle+= M_PI/15*dt*512;
        associated.angleDeg = angle;
    }
    if(instance.IsKeyDown(A_KEY)){
        angle -= M_PI/15*dt*512;
        associated.angleDeg = angle;
    }
    penguinPos+= speed.Normalized().Rotate(angle/180*M_PI)*dt*8;
    associated.box.x = penguinPos.x;
    associated.box.y = penguinPos.y;
    if(hp <= 0){
        if(shared_ptr<GameObject> go = pcannon.lock()){
            go->RequestDelete();
        }
        associated.RequestDelete();
        Camera::Unfollow();
    }

}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type){
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet != nullptr){
        if(bullet->targetsPlayer){
            hp -= bullet->GetDamage();
            cout << "Vida do Penguin: " << hp << endl;
            other.RequestDelete();
            if(hp <= 0){
                GameObject* go = new GameObject();
                State* instance = &Game::GetInstance().GetState();
                Sprite* sprite = new Sprite(*go, "assets/img/penguindeath.png", 5, 3.0/30.0, 15.0/30.0);
                go->box.x = associated.box.GetCenter().x - go->box.w/2;
                go->box.y = associated.box.GetCenter().y - go->box.h/2;
                Sound* sound = new Sound(*go, "assets/audio/boom.wav");
                sound -> Volume(10);
                sound -> Play(0);
                go->AddComponent(sound);
                go->AddComponent(sprite);
                instance->AddObject(go); 
            }
        }
    }
}

Rect PenguinBody::GetPosition(){
    return associated.box;
}
