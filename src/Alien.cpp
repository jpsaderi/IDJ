#include "../include/Alien.hpp"
#include "../include/Game.hpp"
#include "../include/PenguinBody.hpp"

int Alien::alienCount = 0;
bool Alien::delayStart = true;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
    Sprite* sprite = new Sprite(associated, "./assets/img/alien.png");
    associated.AddComponent(sprite);
    hp = 100;
    speed = Vec2(0, 0);
    this -> nMinions = nMinions;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
    alienCount++;
    state = RESTING;
    restTimer.Restart();
    this -> timeOffset = rand() % 5 + 2;
}

Alien::~Alien(){
    for(unsigned int i = 0; i < minionArray.size(); i++){
        if(shared_ptr<GameObject> go = minionArray[i].lock()){
            go -> RequestDelete();
        }
    }
    alienCount--;
}

void Alien::Start(){
    for(int i = 0; i < nMinions; i++){
        State* instance = &Game::GetInstance().GetCurrentState();
        GameObject* go = new GameObject();
        weak_ptr<GameObject> alienCenter = instance -> GetObjectPtr(&associated);
        Minion *minion = new Minion(*go, alienCenter, (M_PI*(1+2*i*360/nMinions))/360);
        go -> AddComponent(minion);
        minionArray.push_back(instance -> AddObject(go));
    }
}

void Alien::Render(){

}

void Alien::Update(float dt){
    int spd = 256;
    InputManager input= InputManager::GetInstance();
    if(hp <= 0){
        associated.RequestDelete();
    }
    else{
        restTimer.Update(dt);
        Vec2 alien_pos = Vec2(associated.box.x, associated.box.y);
        if(state == RESTING){
            if((restTimer.Get() >= 0.5+timeOffset) && delayStart == false){
                Vec2 destiny_center;
                PenguinBody* pbody = PenguinBody::player;
                if(pbody != nullptr){
                    destiny_center.x = pbody -> GetPosition().GetCenter().x - associated.box.w/2;
                    destiny_center.y = pbody -> GetPosition().GetCenter().y - associated.box.h/2;
                    destination = Vec2(destiny_center.x, destiny_center.y);
                    speed = (destiny_center-alien_pos).Normalized();
                    state = MOVING;
                }
                timeOffset = 0;
            }
        }

        associated.angleDeg -= M_PI/180*dt*spd*8;

        if(state == MOVING){
            bool arrived = false;
            alien_pos += speed*dt*spd;
            if(std::abs(alien_pos.dist(destination)) <= 325){
                arrived = true;
                speed = Vec2(0, 0);
            }
            associated.box.x = alien_pos.x;
            associated.box.y = alien_pos.y;
            if(arrived == true){
                Vec2 destiny_center;
                PenguinBody* pbody = PenguinBody::player;
                if(pbody != nullptr){
                    destiny_center.x = pbody -> GetPosition().GetCenter().x;
                    destiny_center.y = pbody -> GetPosition().GetCenter().y;
                    destination = Vec2(destiny_center.x, destiny_center.y);

                    int minionN = ClosestMinion(destination);
                    if(minionN != -1){
                        if(shared_ptr<GameObject> go = minionArray[minionN].lock()){
                            Minion* minion = (Minion*) go -> GetComponent("Minion");
                            minion -> Shoot(destination);
                        }
                    state = RESTING;
                    restTimer.Restart();
                    }
                }
            }

        }
    }
}

bool Alien::Is(string type){
    return type == "Alien";
}

void Alien::NotifyCollision(GameObject& other){
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if(bullet != nullptr){
        if(!bullet->targetsPlayer){
            other.RequestDelete();
            hp -= bullet->GetDamage();
            cout << "Vida do Alien: " << hp << endl;
            if(hp <= 0){
                GameObject* go = new GameObject();
                State* instance = &Game::GetInstance().GetCurrentState();
                go -> angleDeg = associated.angleDeg;
                Sprite* sprite = new Sprite(*go, "assets/img/aliendeath.png",4, 3.0/30.0, 12.0/30.0);
                go->box.x = associated.box.GetCenter().x - go->box.w/2;
                go->box.y = associated.box.GetCenter().y - go->box.h/2;
                Sound* sound = new Sound(*go, "assets/audio/boom.wav");
                sound -> Volume(5);
                sound -> Play(0);
                go->AddComponent(sound);
                go->AddComponent(sprite);
                instance -> AddObject(go);
                for(unsigned int i = 0; i < minionArray.size(); i++){
                    if(shared_ptr<GameObject> go = minionArray[i].lock()){
                        GameObject* go2 = new GameObject();
                        go2 -> angleDeg = go -> angleDeg;
                        
                        Sprite* minionSprite = (Sprite*) go -> GetComponent("Sprite");
                        Vec2 scale = minionSprite -> GetScale();
                        
                        Sprite* sprite = new Sprite(*go2, "./assets/img/aliendeath.png",4,3.0/30.0,12.0/30.0);
                        sprite -> SetScale(scale.x*0.5, scale.y*0.5);
                        
                        go2 -> box.x = go -> box.GetCenter().x - go2 -> box.w/2;
                        go2 -> box.y = go -> box.GetCenter().y - go2 -> box.h/2;
                        Sound* sound = new Sound(*go2, "assets/audio/boom.wav");
                        sound -> Volume(5);
                        sound -> Play(0);
                        go2->AddComponent(sound);
                        go2->AddComponent(sprite);
                        instance -> AddObject(go2);
                    }
                }
            }
        }       
    }
}

int Alien::ClosestMinion(Vec2 pos){
    int minion;
    float min_distance = INT32_MAX;
    for(unsigned int i = 0; i < minionArray.size(); i++){
        if(shared_ptr<GameObject> go = minionArray[i].lock()){
            Vec2 aux = Vec2(go -> box.x, go -> box.y);
            float dist = aux.dist(pos);
            if(dist <= min_distance){
                min_distance = dist;
                minion = i;
            }
        }
    }
    return minion;
}