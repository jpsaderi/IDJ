#include "../include/Face.hpp"

Face::Face(GameObject& associated) : Component(associated){
    this -> hitpoints = 30;
}

void Face::Damage(int damage){
    this -> hitpoints -= damage;
    if (hitpoints <= 0){
        Sound* death = (Sound*) this -> associated.GetComponent("Sound");
        associated.RequestDelete();
        if(death != nullptr){
            death -> Volume(10);
            death -> Play(0); 
        }
    }
}

void Face::Update(float dt){

}

void Face::Render(){

}

bool Face::Is(string type){
    return type == "Face";
}
