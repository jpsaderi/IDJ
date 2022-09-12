#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Component.hpp"
#include "Minion.hpp"
#include "SDL_include.h"
#include <string>

using namespace std;

#define MV Action::ActionType::MOVE
#define SHT Action::ActionType::SHOOT


class Alien : public Component{
private:
    class Action{
    private:

    public:
        enum ActionType {MOVE, SHOOT};
        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos; 
    };

    Vec2 speed;
    int hp;
    int nMinions;
    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;

public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);

    int ClosestMinion(Vec2 pos);
};

#endif