#ifndef SPRITE_HPP
#define SPRITE_HPP

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include <string>
#include "Component.hpp"
#include "Resources.hpp"

using namespace std;

class Sprite : public Component{
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, string file);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(float x, float y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(string type);
    void Update(float dt);
};

#endif