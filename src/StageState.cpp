#include "../include/StageState.hpp"
#include "../include/Game.hpp"
#include "../include/EndState.hpp"
#include "../include/PenguinBody.hpp"

StageState::StageState(){
    tileSet = nullptr;
    quitRequested = false;
    started = false;

    GameData::playerVictory = false;
}

StageState::~StageState(){
    objectArray.clear();
}

void StageState::LoadAssets(){
    GameObject* go = new GameObject();
    GameObject* oceango = new GameObject();
    Sprite* bg = new Sprite(*oceango, "assets/img/ocean.jpg");
    oceango->AddComponent(bg);

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
	
	backgroundMusic = new Music("./assets/audio/stageState.ogg");

    for(int i = 0; i < N_ALLIENS; i++){
        GameObject* AlienGO = new GameObject();
        AlienGO -> box.x = rand()%1200 - AlienGO -> box.w/2;
        AlienGO -> box.y = rand()%1300 - AlienGO -> box.h/2;

        Alien* alien = new Alien(*AlienGO, 5);
        AlienGO -> AddComponent(alien);
        objectArray.emplace_back(AlienGO);
    }

	GameObject* PenguinGO = new GameObject();
	PenguinGO -> box.x = 704 - PenguinGO -> box.w/2;
	PenguinGO -> box.y = 640 - PenguinGO -> box.h/2;

	PenguinBody* penguin = new PenguinBody(*PenguinGO);
	PenguinGO -> AddComponent(penguin);

	Camera::Follow(PenguinGO);
	
	objectArray.emplace_back(PenguinGO);

    backgroundMusic -> Volume(50);
    backgroundMusic -> Play();
    Alien::delayStart = true;
}



void StageState::Update(float dt){
    if(PenguinBody::player == nullptr){
        GameData::playerVictory = false;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
        cout << "Player is dead" << endl;
    }
    else if(Alien::alienCount == 0){
        GameData::playerVictory = true;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    else{
        InputManager instance = InputManager::GetInstance();
        if(instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested() == true){
            popRequested = true;
            backgroundMusic -> Stop();
            Camera::Unfollow();
            Camera::pos = Vec2(0,0);
        }

        Camera::Update(dt);

        for(unsigned int i = 0; i < objectArray.size(); i++){
            objectArray[i] -> Update(dt);
        }

        for(unsigned int i = 0; i < objectArray.size(); i++){
            Collider* collider = (Collider*) objectArray[i] -> GetComponent("Collider");
            if(collider == nullptr){
                continue;
            }
            for(unsigned int j = i+1; j < objectArray.size(); j++){
                Collider* collider2 = (Collider*) objectArray[j] -> GetComponent("Collider");
                if(collider2 == nullptr){
                    continue;
                }
                if(collider -> IsColliding(*collider2)){
                    objectArray[i] -> NotifyCollision(*objectArray[j]);
                    objectArray[j] -> NotifyCollision(*objectArray[i]);
                }
            }
        }
        
        for(unsigned int i = 0, j = objectArray.size() ; i < j;i++){
            if(objectArray[i] -> IsDead()){
                objectArray.erase(objectArray.begin()+i);
                i--;
                j--;
            }
        }

        Alien::delayStart = false;
    }
}

void StageState::Render(){
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i] -> Render();
    }
}

void StageState::Start(){
    LoadAssets();
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i] -> Start();
    }
    started = true;
}

void StageState::Pause(){
    
}

void StageState::Resume(){
    
}