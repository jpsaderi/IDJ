#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "SDL_include.h"
#include "Component.hpp"
#include "Minion.hpp"
#include "Collider.hpp"
#include "Timer.hpp"
#include <string>

using namespace std;

// #define MV Action::ActionType::MOVE
// #define RST Action::ActionType::RESTING


class Alien : public Component{
private:
    enum AlienState {MOVING, RESTING};
    AlienState state;
    vector<weak_ptr<GameObject>> minionArray;
    int hp;
    int nMinions;
    Vec2 destionation;
    Vec2 speed;
    Timer restTimer;
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
};

#endif