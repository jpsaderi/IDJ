#include "../include/State.hpp"

State::State(){
	quitRequested = false;
	started = false;
	popRequested = false;
}

State::~State(){
	objectArray.clear();
}

void State::LoadAssets(){

}

void State::Update(float dt){

}

void State::Render(){

}

void State::Start(){

}

void State::Pause(){

}

void State::Resume(){

}

weak_ptr<GameObject> State::AddObject(GameObject* go){
	shared_ptr<GameObject> shared_ptr_go(go);
	objectArray.push_back(shared_ptr_go);
	if(started == true){
		shared_ptr_go -> Start();
	}
	weak_ptr<GameObject> weak_ptr_go(shared_ptr_go);
	return weak_ptr_go;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		if(objectArray[i].get() == go){
			weak_ptr<GameObject> weak_ptr_go(objectArray[i]);
			return weak_ptr_go;
		}
	}
	return {}; //Retorna vazio
}

bool State::PopRequested(){
	return popRequested;
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::StartArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i] -> Start();
	}
}

void State::UpdateArray(float dt){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i] -> Update(dt);
	}
}

void State::RenderArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i] -> Render();
	}
}