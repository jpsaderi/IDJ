#include "../include/Minion.hpp"
#include "../include/Game.hpp"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated){ 
    Sprite* sprite = new Sprite(associated, "./assets/img/minion.png");
    associated.AddComponent(sprite);
    double scale = (double)rand() / (double)(RAND_MAX/0.5)+1;
    // double scale = 2;
    sprite -> SetScale(scale, scale);
    this -> alienCenter = alienCenter;
    if(shared_ptr<GameObject> go = alienCenter.lock()){
        associated.box.x = go->box.Center().x+200-associated.box.w/2;
        associated.box.y = go->box.Center().y+0-associated.box.h/2;
    } 
    arc = arcOffsetDeg;
    associated.angleDeg = arcOffsetDeg;

}

void Minion::Shoot(Vec2 target){
    Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
    Vec2 pos = Vec2(associated.box.Center().x + associated.box.w/2 - sprite->GetWidth()/2, associated.box.Center().y - sprite->GetHeight()/2);
    float angle = pos.anglex2(target);
    Vec2 aux = Vec2(sprite->GetWidth()/2, 0).GetRotated(angle)+pos;
    GameObject *go = new GameObject();

    go -> box.x = aux.x;
    go -> box.y = aux.y;
    go -> angleDeg = angle*180/M_PI;

    Bullet* bullet = new Bullet(*go, angle, 512, 50, 1024, "./assets/img/minionbullet1.png");
    go -> AddComponent(bullet);
    State* instance = &Game::GetInstance().GetState();
    instance -> AddObject(go);
}

void Minion::Render(){

}

void Minion::Start(){

}

void Minion::Update(float dt){
    Vec2 center_pos = alienCenter.lock()->box.Center();
    Vec2 aux = Vec2(100, 0).GetRotated(arc) + center_pos;
    arc += 2*M_PI/360*dt*64;

    associated.box.x = aux.x-associated.box.w/2;
    associated.box.y = aux.y-associated.box.h/2;

    Vec2 pos = associated.box.Center();
    associated.angleDeg = (pos.anglex2(center_pos)*360)/(2*M_PI);
}

bool Minion::Is(string type){
    return type == "Minion";
}