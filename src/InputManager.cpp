#include "../include/InputManager.hpp"

InputManager::InputManager(){
    for(int i = 0; i < 6; i++){
        mouseState[i] = 0;
        mouseUpdate[i] = 0;
    }
    
    mouseX = 0;
    mouseY = 0;
    
    updateCounter = 0;
    quitRequested = false;
}

InputManager::~InputManager(){

}

void InputManager::Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    updateCounter += 1;
    quitRequested = false;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            quitRequested = true;
        }
        else{
            if(event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == false){
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
            }
            else if(event.type == SDL_MOUSEBUTTONUP){
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
            }
            if(event.type == SDL_KEYDOWN && event.key.repeat == false){
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
            else if(event.type == SDL_KEYUP){
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
        }
    }
}

bool InputManager::KeyPress(int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it -> second == updateCounter){
            return keyState.find(key) -> second;
        }
        else{
            return false;
        }
    }
    return false;    
}

bool InputManager::KeyRelease(int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it -> second == updateCounter){
            return !keyState.find(key) -> second;
        }
        else{
            return false;
        }
    }
    return false;
}

bool InputManager::IsKeyDown(int key){
    auto it = keyState.find(key);
    if(it != keyState.end()){
        return it -> second;
    }
    return false;
}

bool InputManager::MousePress(int button){
    if(mouseUpdate[button] == updateCounter){
        return !mouseState[button];
    }
    return false;
}

bool InputManager::MouseRelease(int button){
    if(mouseUpdate[button] == updateCounter){
        return !mouseState[button];
    }
    return false;
}

bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}