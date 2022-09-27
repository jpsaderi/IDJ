#include "../include/EndState.hpp"
#include "../include/PenguinBody.hpp"
#include "../include/Game.hpp"
#include "../include/TitleState.hpp"

EndState::EndState(){
    Camera::pos = Vec2(0,0);   

    if(GameData::playerVictory == true){
        GameObject* go = new GameObject();
        Sprite* win = new Sprite(*go, "assets/img/win.jpg");
        go -> box.x = 0;
        go -> box.y = 0;
        go -> AddComponent(win);
        objectArray.emplace_back(go);

        GameObject* goText = new GameObject();
        SDL_Color color = {0,0,0,255};
        Text* text = new Text(*goText, "assets/font/Call me maybe.ttf", 20, Text::BLENDED, "ESC para sair do jogo, ou espaco para jogar de novo", color);
        goText -> box.x = 300;
        goText -> box.y = 500;
        goText -> AddComponent(text);
        objectArray.emplace_back(goText);

        backgroundMusic = new Music("assets/audio/endStateWin.ogg");
        backgroundMusic -> Volume(50);
        backgroundMusic -> Play();
    }
    else if(PenguinBody::player == nullptr){
        GameObject* go = new GameObject();
        Sprite* lose = new Sprite(*go, "assets/img/lose.jpg");
        go -> box.x = 0;
        go -> box.y = 0;
        go -> AddComponent(lose);
        objectArray.emplace_back(go);

        GameObject* goText = new GameObject();
        SDL_Color color = {0,0,0,255};
        Text* text = new Text(*goText, "assets/font/Call me maybe.ttf", 20, Text::BLENDED, "ESC para sair do jogo, ou espaco para jogar de novo", color);
        goText -> AddComponent(text);
        goText -> box.x = 300;
        goText -> box.y = 500;
        objectArray.emplace_back(goText);

        backgroundMusic = new Music("assets/audio/endStateLose.ogg");
        backgroundMusic -> Volume(50);
        backgroundMusic -> Play();
    }
}

EndState::~EndState(){
    objectArray.clear();
    backgroundMusic -> Stop();
}

void EndState::LoadAssets(){

}

void EndState::Update(float dt){
    InputManager instance = InputManager::GetInstance();
    if(instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested() == true){
        quitRequested = true;
    }
    if(instance.KeyPress(SPACE_KEY)){
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
    UpdateArray(dt);
}

void EndState::Render(){
    Camera::pos = Vec2(0,0);
    RenderArray();
}

void EndState::Start(){

}

void EndState::Pause(){

}

void EndState::Resume(){

}