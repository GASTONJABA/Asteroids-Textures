#include "AsteroidManager.h"
#include <raymath.h>
#include <cstdlib>

AsteroidManager::AsteroidManager(const char* fileName1, const char* fileName2, const char* fileName3) {
    texture1 = LoadTexture(fileName1);
    texture2 = LoadTexture(fileName2);
    texture3 = LoadTexture(fileName3);
}
AsteroidManager::~AsteroidManager() {
    UnloadTexture(texture1);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
}


void AsteroidManager::SpawnInitial(int count)
{
    for (int c = 0; c < count; c++)
    {
        for (int i = 0; i < maxLarge; i++)
        {
            if (!largeAsteroids[i].active)
            {
                Vector2 pos;
                Vector2 target;

                int side = rand() % 4; // 0=arriba,1=derecha,2=abajo,3=izquierda
                switch (side)
                {
                case 0: // arriba
                    pos = { (float)(rand() % GetScreenWidth()), -50.0f };
                    break;
                case 1: // derecha
                    pos = { (float)GetScreenWidth() + 50.0f, (float)(rand() % GetScreenHeight()) };
                    break;
                case 2: // abajo
                    pos = { (float)(rand() % GetScreenWidth()), (float)GetScreenHeight() + 50.0f };
                    break;
                case 3: // izquierda
                    pos = { -50.0f, (float)(rand() % GetScreenHeight()) };
                    break;
                }

                target = { (float)(rand() % GetScreenWidth()), (float)(rand() % GetScreenHeight()) };
                Vector2 dir = Vector2Normalize(Vector2Subtract(target, pos));

                largeAsteroids[i].Spawn(pos, AsteroidSize::Large, { dir.x * 2.0f, dir.y * 2.0f });
                break;
            }
        }
    }
}


void AsteroidManager::Update(float deltaTime)
{
    for (int i = 0; i < maxLarge; i++)   largeAsteroids[i].Update(deltaTime);
    for (int i = 0; i < maxMedium; i++)  mediumAsteroids[i].Update(deltaTime);
    for (int i = 0; i < maxSmall; i++)   smallAsteroids[i].Update(deltaTime);
}

void AsteroidManager::Draw()
{
    for (int i = 0; i < maxLarge; i++)   largeAsteroids[i].Draw(texture1);
    for (int i = 0; i < maxMedium; i++)  mediumAsteroids[i].Draw(texture2);
    for (int i = 0; i < maxSmall; i++)   smallAsteroids[i].Draw(texture3);
}

bool AsteroidManager::CheckCollisionsWithPlayer(Vector2 playerPos, float playerRadius)
{
    Asteroid* arrays[3] = { largeAsteroids, mediumAsteroids, smallAsteroids };
    int maxs[3] = { maxLarge, maxMedium, maxSmall };

    for (int size = 0; size < 3; size++)
    {
        for (int i = 0; i < maxs[size]; i++)
        {
            if (!arrays[size][i].active) continue;
            float dist = Vector2Distance(playerPos, arrays[size][i].position);
            if (dist < playerRadius + arrays[size][i].radius)
            {
                Vector2 parentVel = arrays[size][i].velocity;
                arrays[size][i].active = false;

                if (size == 0)
                {
                    int created = 0;
                    for (int j = 0; j < maxMedium && created < 2; j++)
                    {
                        if (!mediumAsteroids[j].active)
                        {
                            mediumAsteroids[j].Spawn(arrays[size][i].position, AsteroidSize::Medium, parentVel);
                            created++;
                        }
                    }
                }
                else if (size == 1)
                {
                    int created = 0;
                    for (int j = 0; j < maxSmall && created < 2; j++)
                    {
                        if (!smallAsteroids[j].active)
                        {
                            smallAsteroids[j].Spawn(arrays[size][i].position, AsteroidSize::Small, parentVel);
                            created++;
                        }
                    }
                }

                return true;
            }
        }
    }

    return false;
}

bool AsteroidManager::CheckCollisionsWithBullets(Bullet* bullets, int bulletCount)
{
    bool hit = false;

    for (int b = 0; b < bulletCount; b++)
    {
        if (!bullets[b].IsActive()) continue;

        Asteroid* arrays[3] = { largeAsteroids, mediumAsteroids, smallAsteroids };
        int maxs[3] = { maxLarge, maxMedium, maxSmall };

        for (int size = 0; size < 3; size++)
        {
            for (int i = 0; i < maxs[size]; i++)
            {
                if (!arrays[size][i].active) continue;

                float dist = Vector2Distance(bullets[b].GetPosition(), arrays[size][i].position);
                if (dist < bullets[b].GetRadius() + arrays[size][i].radius)
                {
                    Vector2 parentVel = arrays[size][i].velocity;
                    arrays[size][i].active = false;

                    if (size == 0)
                    {
                        int created = 0;
                        for (int j = 0; j < maxMedium && created < 2; j++)
                        {
                            if (!mediumAsteroids[j].active)
                            {
                                mediumAsteroids[j].Spawn(arrays[size][i].position, AsteroidSize::Medium, parentVel);
                                created++;
                            }
                        }
                    }
                    else if (size == 1)
                    {
                        int created = 0;
                        for (int j = 0; j < maxSmall && created < 2; j++)
                        {
                            if (!smallAsteroids[j].active)
                            {
                                smallAsteroids[j].Spawn(arrays[size][i].position, AsteroidSize::Small, parentVel);
                                created++;
                            }
                        }
                    }

                    bullets[b].Deactivate();
                    hit = true;
                    break;
                }
            }
            if (hit) break;
        }
    }

    return hit;
}



Asteroid* AsteroidManager::GetAllAsteroids(int size)
{
    if (size == 0) return largeAsteroids;
    if (size == 1) return mediumAsteroids;
    return smallAsteroids;
}

int AsteroidManager::GetMaxAsteroids(int size) const
{
    if (size == 0) return maxLarge;
    if (size == 1) return maxMedium;
    return maxSmall;
}