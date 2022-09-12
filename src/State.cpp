#include "../include/State.hpp"

State::State(){
	GameObject* go = new GameObject();
	GameObject* oceango = new GameObject();
	Sprite* bg = new Sprite(*oceango, "./assets/img/ocean.jpg");
    oceango -> AddComponent(bg);

	CameraFollower* CF = new CameraFollower(*oceango);
	oceango -> AddComponent(CF);

	oceango -> box.x = Camera::pos.x;
	oceango -> box.y = Camera::pos.y;

	objectArray.emplace_back(oceango);

	TileSet* tileset = new TileSet(64, 64, "./assets/img/tileset.png");

	TileMap* tilemap = new TileMap(*go, "./assets/map/tileMap.txt", tileset);
	go -> AddComponent(tilemap);
	go -> box.x = 0;
	go -> box.y = 0;
	objectArray.emplace_back(go);
	
	music.Open("./assets/audio/stageState.ogg");
	
	GameObject* AlienGO = new GameObject();
	AlienGO -> box.x = 512 - AlienGO -> box.w/2;
	AlienGO -> box.y = 300 - AlienGO -> box.h/2;

	Alien* alien = new Alien(*AlienGO, 5);
	AlienGO -> AddComponent(alien);
	// Camera::Follow(AlienGO);

	objectArray.emplace_back(AlienGO);

	quitRequested = false;
	started = false;
}

void State::LoadAssets(){
    music.Volume(25);
    music.Play();
}

void State::Update(float dt){
	InputManager instance = InputManager::GetInstance();
	if(instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested() == true){
		quitRequested = true;
	}

	Camera::Update(dt);
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i] -> Update(dt);
    }
    for(unsigned int i = 0; i < objectArray.size(); i++){
        if (objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i] -> Render();
	}
}

bool State::QuitRequested(){
    return quitRequested;
}

State::~State(){
    objectArray.clear(); 
}

void State::Start(){
	LoadAssets();
	for(unsigned int i = 0; i < objectArray.size(); i++){
		// objectArray[i].get() -> Start();
		objectArray[i] -> Start();
	}
	started = true;	
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