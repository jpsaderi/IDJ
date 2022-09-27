#include "../include/Game.hpp"

Game* Game::instance = nullptr;
stack <unique_ptr<State>> Game::stateStack;

Game::Game(string title, int width, int height){
    if (instance != nullptr){
        printf("Logic Problem\n");
    }
    else{
        instance = this;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        printf("SDL_Init fail\n");
        cout << SDL_GetError() << endl;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        printf("IMG Init fail\n");
        cout << IMG_GetError() << endl;
    } 

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD) == 0){
        printf("Mix_Init fail\n");
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        printf("MIX_OpenAudio fail\n");
    }
    
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr){
        printf("SDL_CreateWindows fail\n");
        cout << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //OpenGL ou Direct3D
  
    if (renderer == nullptr){
        printf("SDL_CreateRenderer fail\n");
        cout << SDL_GetError() << endl;
    }

    if (TTF_Init() != 0){
        printf("TTF_Init fail\n");
    }
    frameStart = 0;
    dt = 0;
    srand(time(NULL));
    storedState = nullptr;
}

Game::~Game(){
    if(storedState != nullptr){
        delete storedState;
    }
    while(stateStack.empty() == false){
        stateStack.pop();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

Game& Game::GetInstance(){
    if(instance != nullptr){
        return *instance;
    }
    new Game("João Pedro Sadéri da Silva - 170126021", 1024, 600);
    return *instance;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetCurrentState(){
    return *stateStack.top();
}

void Game::Push(State* state){
    storedState = state;
}

void Game::Run(){
    if(storedState != nullptr){
        stateStack.emplace(storedState);
        storedState = nullptr;
        stateStack.top() -> Start();
    }
    else{
        printf("Game Run error\n");
        exit(1);
    }
    while(stateStack.top() -> QuitRequested() == false && stateStack.empty() == false){
        if(stateStack.top() -> PopRequested() == true){
            stateStack.top() -> Pause();
            stateStack.pop();
            if(stateStack.empty() == false){
                stateStack.top() -> Resume();
            }
        }
        if(storedState != nullptr){
            stateStack.top() -> Pause();
            stateStack.emplace(storedState);
            stateStack.top() -> Start();
            storedState = nullptr;
        }

        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top() -> Update(dt);
        stateStack.top() -> Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    while(stateStack.empty() == false){
        stateStack.pop();
    }
    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearFonts();
}

void Game::CalculateDeltaTime(){
    int lastFrame = frameStart;
    frameStart = SDL_GetTicks();
    dt = (frameStart - lastFrame)/1000.0; //conventer para segundos
}

float Game::GetDeltaTime(){
    return dt;
}