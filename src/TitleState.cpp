#include "../include/TitleState.hpp"
#include "../include/Game.hpp"
#include "../include/StageState.hpp"

TitleState::TitleState(){
    GameObject* go = new GameObject();
    Sprite* title = new Sprite(*go, "assets/img/title.jpg");
    go -> box.x = 0;
    go -> box.y = 0;
    go -> AddComponent(title);
    objectArray.emplace_back(go);

    GameObject* go2 = new GameObject();
    SDL_Color color = {0, 0, 0, 255};
    Text* text = new Text(*go2, "assets/font/Call me maybe.ttf", 30, Text::BLENDED, "Pressione espaco para continuar", color);
    go2 -> box.x = 330;
    go2 -> box.y = 500;
    go2 -> AddComponent(text);
    objectArray.emplace_back(go2);

}

TitleState::~TitleState(){
    objectArray.clear();
}

void TitleState::LoadAssets(){
    
}

void TitleState::Update(float dt){
    InputManager instance = InputManager::GetInstance();
	if(instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested())
		quitRequested = true;
    if(instance.KeyPress(SPACE_KEY)){
        Game::GetInstance().Push(new StageState());
    }
    UpdateArray(dt);
}

void TitleState::Render(){
    Camera::pos = Vec2(0,0);
    RenderArray();
}

void TitleState::Start(){
    
}

void TitleState::Pause(){

}

void TitleState::Resume(){
    
}