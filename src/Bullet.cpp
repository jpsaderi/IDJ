#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, bool targetsPlayer) : Component(associated){
    Sprite* spr = new Sprite(associated, sprite, frameCount,0.017);
    associated.box.w = spr -> GetWidth()/2;
    associated.box.h = spr -> GetHeight()/2;
    associated.AddComponent(spr);

    this -> speed = Vec2(1, 0);
    // this -> speed = this -> speed.Rotate(angle)*speed*0.40;
    this -> speed = this -> speed.Rotate(angle)*speed;
    distanceLeft = maxDistance;
    this -> damage = damage;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    this -> targetsPlayer = targetsPlayer;
}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::Start(){

}

void Bullet::Update(float dt){
    Vec2 pos = Vec2(associated.box.x, associated.box.y);
    pos += speed * dt;

    associated.box.x = pos.x;
    associated.box.y = pos.y;

    distanceLeft -= (speed*dt).Magnitude();

    if(distanceLeft <= 0){
        associated.RequestDelete();
    }
}

void Bullet::Render(){
    
}

bool Bullet::Is(string type){
    return type == "Bullet";
}

void Bullet::NotifyCollision(GameObject& other){
    
}