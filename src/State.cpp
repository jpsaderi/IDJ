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
	
	LoadAssets();
	quitRequested = false;
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
	if(instance.KeyPress(SPACE_KEY)){
		Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2(instance.GetMouseX(), instance.GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	}
    Camera::Update(dt);
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i].get() -> Update(dt);
    }
    for(unsigned int i = 0; i < objectArray.size(); i++){
        if (objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i].get() -> Render();
	}
}

bool State::QuitRequested(){
    return quitRequested;
}

State::~State(){
    objectArray.clear(); 
}

void State::AddObject(int mouseX, int mouseY){
    GameObject* go = new GameObject();

	Sprite* image = new Sprite(*go, "assets/img/penguinface.png");

	go -> AddComponent(image);
	// Centraliza o objeto

	// go -> box.x = mouseX - image->GetWidth()/2;
	// go -> box.y = mouseY - image->GetHeight()/2;

	go -> box.x = mouseX - go->box.w/2 + Camera::pos.x;
	go -> box.y = mouseY - go->box.h/2 + Camera::pos.y;

	Sound* sound = new Sound(*go, "assets/audio/boom.wav");
	go -> AddComponent(sound);

	Face* face = new Face(*go);
	go -> AddComponent(face);

	objectArray.emplace_back(go);
}
