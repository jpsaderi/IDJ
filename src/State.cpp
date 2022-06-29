#include "../include/State.hpp"

State::State(){
	GameObject* go = new GameObject();
	GameObject* oceango = new GameObject();
	Sprite* bg = new Sprite(*go, "./assets/img/ocean.jpg");
    
	oceango -> AddComponent(bg);
	oceango -> box.x = 0;
	oceango -> box.y = 0;

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
    Input();
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i].get() -> Update(dt);
    }
    for(unsigned int i = 0; i < objectArray.size(); i++){
        if (objectArray[i]->IsDead()){
			// Sound *sound = (Sound*) objectArray[i] -> GetComponent("Sound");
			// objectArray[i].get() -> RemoveComponent(objectArray[i]->GetComponent("Sprite"));
			// objectArray[i].get() -> RemoveComponent(objectArray[i]->GetComponent("Face"));

			// if((sound != nullptr && sound -> IsOpen() == false) || (sound == nullptr)){
				objectArray.erase(objectArray.begin()+i);
			// }
        }
    }
    // if (SDL_QuitRequested() == true){ //Mantem?
    //     music.Stop();
    //     quitRequested = true;
    // }
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
	// go -> box.x = mouseX;
	// go -> box.y = mouseY;

	// Centraliza o objeto

	go -> box.x = mouseX - image->GetWidth()/2;
	go -> box.y = mouseY - image->GetHeight()/2;

	Sound* sound = new Sound(*go, "assets/audio/boom.wav");

	go -> AddComponent(sound);

	Face* face = new Face(*go);

	go -> AddComponent(face);

	objectArray.emplace_back(go);
}

void State::Input(){
	SDL_Event event;
	int mouseX, mouseY;
	
	SDL_GetMouseState(&mouseX, &mouseY);    // Obtenha as coordenadas do mouse

	while(SDL_PollEvent(&event)){           // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
		if(event.type == SDL_QUIT){         // Se o evento for quit, setar a flag para terminação
			quitRequested = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) { // Se o evento for clique...
			for(int i = objectArray.size() - 1; i >= 0; --i) {  // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
				GameObject* go = (GameObject*) objectArray[i].get();    // Obtem o ponteiro e casta pra Face.
				
				if(go->box.Contains(Vec2(mouseX, mouseY))){
					Face* face = (Face*)go->GetComponent("Face");
					
					if(nullptr != face){
						// printf("Hit\n");
						face->Damage(std::rand() % 10 + 10);// Aplica dano
						break; // Sai do loop (só queremos acertar um)
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			if(event.key.keysym.sym == SDLK_ESCAPE){// Se a tecla for ESC, setar a flag de quit
				quitRequested = true;
			}
			else{// Se não, crie um objeto
				Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}
