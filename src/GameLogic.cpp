#include "GameLogic.h"
#include <raymath.h>
#include <cstdlib>
#include <time.h>

GameLogic::GameLogic()
{
	GameRunning = true;
	InitWindow(1600, 900, "Asteroids");
	InitAudioDevice();                                     // Initialize audio device and context
	// Load music ONE TIME before the game loop
	 music = LoadMusicStream("res/Asteroids.wav");
	PlayMusicStream(music);
	// player.LoadTexturePlayer("res/spaceship.png");
	srand(time(0));
	//Texture2D spriteSheet = LoadTexture("res/Asteroids.png");
	player.LoadTexturePlayer("res/spaceship.png");
	starsManager = new StarsManager("res/StarsBig.png", "res/StarsMedium.png", "res/StarsSmall.png");
	starsManager->SpawnInitial(5);
	asteroidManager = new AsteroidManager("res/asteroidBig.png", "res/asteroidMedium.png", "res/asteroidSmall.png");
	asteroidManager->SpawnInitial(5);
	//Music music = LoadMusicStream("res/mus/Asteroids.wav");


}

GameLogic::~GameLogic()
{
	UnloadMusicStream(music);
	   // Close audio device (music streaming is automatically stopped)
	CloseWindow();
}

void GameLogic::Update()
{
	if (!GameRunning) return;
	//UpdateMusicStream(music);
	float deltaTime = GetFrameTime();
	//PlayMusicStream(music);
	player.Update(deltaTime);
	asteroidManager->Update(deltaTime);
	starsManager->Update(deltaTime);
	asteroidManager->CheckCollisionsWithBullets(player.GetBullets(), player.GetMaxBullets());

	if (asteroidManager->CheckCollisionsWithPlayer(player.GetPosition(), player.GetRadius()))
	{
		player.LoseLife();
		if (player.GetLives() <= 0)
		{
			GameRunning = false;
		}
	}
}

void GameLogic::Run()
{
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		//Music music = LoadMusicStream("res/Asteroids.wav");
		Update();
		
		BeginDrawing();
		//Music music = LoadMusicStream("res/Asteroids.wav");
		//PlayMusicStream(music);
		ClearBackground(BLACK);
		
		player.Draw();
		asteroidManager->Draw();
		starsManager->Draw();
		DrawText(TextFormat("Lives: %d", player.GetLives()), 10, 10, 20, RED);

		if (!GameRunning)
		{
			const char* msg = "YOU LOSE";
			int fontSize = 80;

			int textWidth = MeasureText(msg, fontSize);

			DrawText(msg, (GetScreenWidth() - textWidth) / 2, GetScreenHeight() / 2, fontSize, RED);
		}

		EndDrawing();

	}
}