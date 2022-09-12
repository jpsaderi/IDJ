#include "../include/Bullet.hpp"
#include "../include/Sprite.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated){
    Sprite* spr = new Sprite(associated, sprite);
    associated.AddComponent(spr);

    this -> speed = Vec2(1, 0);
    this -> speed = this -> speed.GetRotated(angle)*speed;
    distanceLeft = maxDistance;
    this -> damage = damage;
}

int Bullet::GetDamage(){
    return damage;
}

bool Bullet::Is(string type){
    return type == "Bullet";
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

void Bullet::Start(){

}

void Bullet::Render(){
    
}