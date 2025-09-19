#pragma once
#include "raylib.h"
#include "Bullet.h"

class Player
{
private:
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float speed;
    float radius;
    Texture2D texture;
    //Texture2D spriteSheet;
   // Rectangle frameRec;
   // Vector2 animPosition;                 
   // float animRotation;                               
   // Vector2 animOrigin; 
    // int frameWidth;             // Ancho de cada frame en el spritesheet
    // int frameHeight; 
    static const int maxBullets = 20;
    Bullet bullets[maxBullets];


    float bulletCooldown;
    float bulletTimer;

    int lives;

    float accelerationRate;
    float decelerationRate;
    float maxSpeed;

public:
    Player();
    ~Player();

    void LoadTexturePlayer(const char* fileName);
    void UnloadTexturePlayer();

    void Update(float deltaTime);
    void Draw();
    void Shoot();
    Vector2 GetPosition();
    float GetRadius();
    Bullet* GetBullets();
    int GetMaxBullets();
    int GetLives();
    void LoseLife();
};