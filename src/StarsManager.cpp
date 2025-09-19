#include "StarsManager.h"
#include "Stars.h"
#include <raymath.h>
#include <cstdlib>

//StarsManager::StarsManager() {};

StarsManager::StarsManager(const char* fileName1, const char* fileName2, const char* fileName3) {
	// Las texturas se cargan en el momento de la creación del objeto
	texture1 = LoadTexture(fileName1);
	texture2 = LoadTexture(fileName2);
	texture3 = LoadTexture(fileName3);
}

StarsManager::~StarsManager() {
	UnloadTexture(texture1);
	UnloadTexture(texture2);
	UnloadTexture(texture3);
}


void StarsManager::SpawnInitial(int count)
{
	for (int c = 0; c < count; c++)
	{
		for (int i = 0; i < maxLarge; i++)
		{
			if (!largeStars[i].active)
				return;


			int side = rand() % 4; // 0=arriba,1=derecha,2=abajo,3=izquierda
			Vector2 pos;
			Vector2 target;
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

			largeStars[i].Spawn(pos, StarsSize::Large, texture1, { dir.x * 2.0f, dir.y * 2.0f });
			break;

		}
	}
}


void StarsManager::Update(float deltaTime)
{
	for (int i = 0; i < maxLarge; i++)   largeStars[i].Update(deltaTime);
	for (int i = 0; i < maxMedium; i++)  mediumStars[i].Update(deltaTime);
	for (int i = 0; i < maxSmall; i++)   smallStars[i].Update(deltaTime);
}

void StarsManager::Draw()
{
	for (int i = 0; i < maxLarge; i++)   largeStars[i].Draw();
	for (int i = 0; i < maxMedium; i++)  mediumStars[i].Draw();
	for (int i = 0; i < maxSmall; i++)   smallStars[i].Draw();
}
Stars* StarsManager::GetAllStars(int size)
{
	if (size == 0) return largeStars;
	if (size == 1) return mediumStars;
	return smallStars; 
}

int StarsManager::GetMaxstars(int size) const
{
	if (size == 0) return maxLarge;
	if (size == 1) return maxMedium;
	return maxSmall;
}