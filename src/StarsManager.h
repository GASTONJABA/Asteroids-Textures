#pragma once
#include "raylib.h"
#include "Stars.h"
#include "Asteroid.h"
class StarsManager
{
private:
	static const int maxLarge = 10;
	static const int maxMedium = maxLarge * 2;
	static const int maxSmall = maxMedium * 2;

	Stars largeStars[maxLarge];
	Stars mediumStars[maxMedium];
	Stars smallStars[maxSmall];

	Texture2D texture1;
	Texture2D texture2;
	Texture2D texture3;

public:
	StarsManager(const char* fileName1, const char* fileName2, const char* fileName3);
	~StarsManager();


	// bool CheckCollisionsWithPlayer(Vector2 playerPos, float playerRadius);
	// bool CheckCollisionsWithBullets(Bullet* bullets, int bulletCount);

	void SpawnInitial(int count);
	void Update(float deltaTime);
	void Draw();

	Stars* GetAllStars(int size); // 0=Large,1=Medium,2=Small
	int GetMaxstars(int size) const;
};




