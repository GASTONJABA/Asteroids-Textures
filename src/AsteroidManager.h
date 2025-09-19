#pragma once
#include "Asteroid.h"
#include "raylib.h"
#include "Bullet.h"

class AsteroidManager
{
private:
	static const int maxLarge = 10;
	static const int maxMedium = maxLarge * 2;
	static const int maxSmall = maxMedium * 2;

	Asteroid largeAsteroids[maxLarge];
	Asteroid mediumAsteroids[maxMedium];
	Asteroid smallAsteroids[maxSmall];

	Texture2D texture1;
	Texture2D texture2;
	Texture2D texture3;

public:
	AsteroidManager(const char* fileName1, const char* fileName2, const char* fileName3);
	~AsteroidManager();

	//void LoadTextureAsteroids(const char* fileName1, const char* fileName2, const char* fileName3);
	//void UnloadTextureAsteroids();

	bool CheckCollisionsWithPlayer(Vector2 playerPos, float playerRadius);
	bool CheckCollisionsWithBullets(Bullet* bullets, int bulletCount);

	void SpawnInitial(int count);
	void Update(float deltaTime);
	void Draw();

	Asteroid* GetAllAsteroids(int size); // 0=Large,1=Medium,2=Small
	int GetMaxAsteroids(int size) const;
};