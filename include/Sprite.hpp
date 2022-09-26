#ifndef SPRITE_HPP
#define SPRITE_HPP

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include <string>
#include "Component.hpp"
#include "Resources.hpp"
#include "Timer.hpp"

using namespace std;

class Sprite : public Component{
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    float secondsToSelfDestruct;

    Timer* selfDestructCount;
    Vec2 scale;
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);

    void SetScale(float scaleX, float ScaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
};

#endif