#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "SDL_include.h"
#include "Collider.hpp"
#include "Component.hpp"
#include "Minion.hpp"
#include "Sound.hpp"
#include "Timer.hpp"
#include <string>

using namespace std;

class Alien : public Component{
private:
    enum AlienState {MOVING, RESTING};
    AlienState state;
    vector<weak_ptr<GameObject>> minionArray;
    int hp;
    int nMinions;
    Vec2 destination;
    Vec2 speed;
    Timer restTimer;
    float timeOffset;
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);

    int ClosestMinion(Vec2 pos);
    static int alienCount;
    static bool delayStart;
};

#endif