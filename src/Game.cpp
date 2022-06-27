#include "../include/Game.hpp"

Game* Game::instance = nullptr;

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
        // cont << Mix_GetError() << endl; 
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        printf("MIX_OpenAudio fail\n");
        // cont << Mix_GetError() << endl;
    }
    
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr){
        printf("SDL_CreateWindows fail\n");
        cout << SDL_GetError() << endl;
    }

    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //OpenGL ou Direct3D
    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    if (renderer == nullptr){
        printf("SDL_CreateRenderer fail\n");
        cout << SDL_GetError() << endl;
    }

    srand(time(NULL));
    state = new State();
}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
State& Game::GetState(){
    return *state;
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
void Game::Run(){
    while(state->QuitRequested() == false){
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}