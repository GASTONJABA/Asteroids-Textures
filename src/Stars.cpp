#include "Stars.h"
#include <cstdlib>
#include <math.h>

Stars::Stars()
{
    texture = { 0 };
    position = { 0, 0 };
    velocity = { 0, 0 };
    radius = 0;
    active = false;
    size = StarsSize::Large;
}

void Stars::Spawn(Vector2 pos, StarsSize s,Texture2D tex , Vector2 parentDir)
{
    position = pos;
    size = s;
    active = true;
    float speed = 0;
    switch (s)
    {
    case StarsSize::Large:  radius = 40; speed = 200; break;
    case StarsSize::Medium: radius = 25; speed = 300; break;
    case StarsSize::Small:  radius = 15; speed = 400; break;
    }

    float angle;
    if (parentDir.x != 0 || parentDir.y != 0)
    {
        float deviation = ((rand() % 60) - 30) * DEG2RAD;
        angle = atan2f(parentDir.y, parentDir.x) + deviation;
    }
    else
    {
        angle = atan2f(parentDir.y, parentDir.x);
    }

    velocity = { cosf(angle) * speed, sinf(angle) * speed };
}

void Stars::Update(float deltaTime)
{
    if (!active) return;

    position.x += velocity.x * deltaTime;
   position.y += velocity.y * deltaTime;

    if (position.x < 0) position.x = (float)GetScreenWidth();
    if (position.x > GetScreenWidth()) position.x = 0;
    if (position.y < 0) position.y = (float)GetScreenHeight();
    if (position.y > GetScreenHeight()) position.y = 0;
}

void Stars::Draw()
{
    if (active)
        //DrawCircleV(position, radius, WHITE);
    {
        Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, radius * 2, radius * 2 };
        Vector2 origin = { (float)radius, (float)radius };
        DrawTexturePro(texture, src, dest, origin, 0.0f, WHITE);
    }
}