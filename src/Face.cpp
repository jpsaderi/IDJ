#include "../include/Face.hpp"

Face::Face(GameObject& associated) : Component(associated){
    this -> hitpoints = 30;
}

void Face::Damage(int damage){
    this -> hitpoints -= damage;
    printf("Hitpoints: %d Damage: %d\n",this->hitpoints, damage);
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
    InputManager instance = InputManager::GetInstance();
    if(instance.MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.box.Contains(Vec2(instance.GetMouseX()+ Camera::pos.x, instance.GetMouseY()+Camera::pos.y))){
            Damage(rand()%10 + 10);
        }
    }
}

void Face::Render(){

}

bool Face::Is(string type){
    return type == "Face";
}

void Face::Start(){
    
}