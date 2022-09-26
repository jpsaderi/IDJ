#include "../include/CameraFollower.hpp"

CameraFollower::CameraFollower(GameObject& go) : Component(go){

}

void CameraFollower::Update(float dt){
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render(){

}


bool CameraFollower::Is(string type){
    return type == "CameraFollower";
}

void CameraFollower::Start(){
    
}

void CameraFollower::NotifyCollision(GameObject& other){
    
}
