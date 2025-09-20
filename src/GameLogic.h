#pragma once
#include "raylib.h" 
#include "Player.h"
#include "AsteroidManager.h"
#include "StarsManager.h"
class GameLogic
{
private:
    Player player;
    AsteroidManager* asteroidManager;
    StarsManager* starsManager;
    bool GameRunning;
    void Update();
    Music music;
public:
    GameLogic();
    ~GameLogic();
    void Run();

};
