#include "../include/PenguinCannon.hpp"
#include "../include/Game.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinCenter) : Component(associated) {
    pbody = penguinCenter;
    angle = 0;
    Sprite* sprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(sprite);
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
    timer = nullptr;
}	

void PenguinCannon::Shoot(){  
    if(timer == nullptr || timer -> Get() >= 0.5){
        Sprite* sprite = (Sprite*) associated.GetComponent("Sprite");

        Vec2 pos = associated.box.GetCenter();
        Vec2 aux = Vec2(sprite -> GetWidth()/2, 0).Rotate(angle)+pos;

        GameObject* go = new GameObject();
        go -> box.x = aux.x;
        go -> box.y = aux.y;
        go -> angleDeg = angle*180/M_PI;

        Bullet* bullet = new Bullet(*go, angle, 512, 10, 1024, "assets/img/penguinbullet.png", 4, false);
        go -> AddComponent(bullet);

        State* instance = &Game::GetInstance().GetState();
        instance -> AddObject(go);
    
        if(timer == nullptr){
            timer = new Timer();
        }
        timer -> Restart();
    }
}

void PenguinCannon::Start(){

}

void PenguinCannon::Update(float dt){
    InputManager instance = InputManager::GetInstance();
    if(timer != nullptr){
        timer -> Update(dt);
    }
    if(shared_ptr<GameObject> go = pbody.lock()){
        associated.box.x = go -> box.GetCenter().x - associated.box.w/2;
        associated.box.y = go -> box.GetCenter().y - associated.box.h/2;
        Vec2 centerpos = Vec2(instance.GetMouseX()+Camera::pos.x, instance.GetMouseY()+Camera::pos.y);
        Vec2 pos = associated.box.GetCenter();
        angle = pos.anglex2(centerpos);
        associated.angleDeg = angle*180/M_PI;
        if(instance.IsMouseDown(LEFT_MOUSE_BUTTON)){
            Shoot();
        }
    }
    else{
        associated.RequestDelete();
    }
}

void PenguinCannon::Render(){

}

bool PenguinCannon::Is(string type){
    return type == "PenguinCannon";
}   

void PenguinCannon::NotifyCollision(GameObject& other){
    
}