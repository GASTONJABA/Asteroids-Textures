#pragma once
#include "raylib.h"

class Bullet
{
private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool active;
 

public:
    Bullet();

    void Fire(Vector2 startPos, float rotation, float speed);
    void Update(float deltaTime);
    void Draw();
    Vector2 GetPosition();
    float GetRadius();
    bool IsActive();
    void Deactivate();
};