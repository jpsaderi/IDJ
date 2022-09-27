#include "../include/Text.hpp"
#include "../include/Game.hpp"

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated){
    this -> fontFile = fontFile;
    this -> fontSize = fontSize;
    this -> style = style;
    this -> text = text;
    this -> color = color;
    this -> texture = nullptr;
    font = Resources::GetFont(fontFile, fontSize);
    RemakeTexture();
}

Text::~Text(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    texture = nullptr;
}

void Text::Start(){

}

void Text::Update(float dt){

}

void Text::Render(){
    if(texture != nullptr){
        SDL_Rect dstRect, clipRect;
        dstRect.x = associated.box.x - Camera::pos.x;
        dstRect.y = associated.box.y - Camera::pos.y;
        dstRect.w = associated.box.w;
        dstRect.h = associated.box.h;

        clipRect = dstRect;
        clipRect.x = 0;
        clipRect.y = 0;

        if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstRect) != 0){
            cout << SDL_GetError() << ':' << texture << endl;
        }
    }
}

bool Text::Is(string type){
    return type == "Text";
}

void Text::NotifyCollision(GameObject& other){

}

void Text::SetText(string text){
    this -> text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this -> color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this -> style = style;
    RemakeTexture();
}

void Text::SetFontFile(string fontFile){
    this -> fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this -> fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface* surface = nullptr;
    switch(style){
        case SOLID:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
        case SHADED:
            surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, SDL_Color{0, 0, 0, 0});
            break;
        case BLENDED:
            surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
            break;
        default:
            surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
            break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    if(texture == nullptr){
        cout << "Nao foi possivel carregar textura de texto" << endl;
        cout << SDL_GetError() << endl;
        exit(-1);
    }
    SDL_FreeSurface(surface);
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    associated.box.w = w;
    associated.box.h = h;
}