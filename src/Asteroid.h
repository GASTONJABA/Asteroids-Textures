#pragma once
#include "raylib.h"

enum  class AsteroidSize { Large, Medium, Small };

class Asteroid
{
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool active;
    AsteroidSize size;

    Asteroid();
    void Spawn(Vector2 pos, AsteroidSize s, Vector2 parentDir = { 0,0 });
    void Update(float deltaTime);
    void Draw(Texture2D texture);
    //int Break(Asteroid* pool, int poolSize);
private:
    Texture2D texture; // Add this line to store the texture
};