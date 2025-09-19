#include "Player.h"
#include <math.h>
#include <raymath.h>

Player::Player()
{
	position = { 1600 / 2, 900 / 2 };
	velocity = { 0.0f, 0.0f };
	rotation = 0.0f;
	speed = 0.0f;
	texture = { 0 };
	//spriteSheet = LoadTexture("res/Asteroids.png");
	bulletCooldown = 0.25f;
	bulletTimer = 0.0f;
	lives = 13;
	radius = 10;
	accelerationRate = 500.0f;
	decelerationRate = 2.5f;
	maxSpeed = 300.0f;
	//frameWidth = spriteSheet.width / 6;                // Ancho de cada frame en el spritesheet
	//frameHeight = spriteSheet.height;

	//frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight }; // Rectángulo que define el frame actual para dibujar
	//animPosition = { 400.0f, 300.0f };                    // Posición donde se dibuja la animación
	//animRotation = 0.0f;                                    // Ángulo de rotación de la animación
	//animOrigin = { frameWidth / 2.0f, frameHeight / 2.0f }; // Origen para rotar en el centro del frame
	// Tiempo en segundos que dura cada frame


}

Player::~Player() {}

void Player::LoadTexturePlayer(const char* fileName)
{
	texture = LoadTexture(fileName);
	radius = (float)(texture.width / 2);
	//spriteSheet = LoadTexture("res/Asteroids.png");

}

void Player::UnloadTexturePlayer()
{
	UnloadTexture(texture);
	//UnloadTexture(spriteSheet);
}








void Player::Update(float deltaTime)
{
	
	Vector2 mousePos = GetMousePosition();
	Vector2 dir = Vector2Subtract(mousePos, position);
	Vector2 normDir = Vector2Normalize(dir);
	rotation = atan2f(dir.y, dir.x) * (180.0f / PI);
	//int currentFrame = 0;                                         // Índice del frame actual de la animación (0 a 5)
	///float frameTime = 0.0f;                                       // Tiempo acumulado para cambiar frame
	//const float frameSpeed = 0.1f;                                // Tiempo en segundos que dura cada frame

	// Velocidades para movimiento y rotación
	//float moveSpeed = 200.0f;
	//float rotationSpeed = 90.0f;
	// --- Animación cuadro por cuadro ---
	//frameTime += delta;					     // Acumula tiempo desde el último frame
	//if (frameTime >= frameSpeed) {			 // Si pasa el tiempo para cambiar frame:
		//frameTime -= frameSpeed;             // Resta el tiempo de un frame (no reinicia a 0 para precisión)

		//currentFrame++;                    // Avanza al siguiente frame
		//if (currentFrame >= 6)            // Si pasó el último frame, vuelve al primero
			///currentFrame = 0;

		//frameRec.x = (float)currentFrame * frameWidth; // Actualiza rectángulo para el frame actual
		//rotation = atan2f(dir.y, dir.x) * (180.0f / PI);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		velocity.x += normDir.x * accelerationRate * deltaTime;
		velocity.y += normDir.y * accelerationRate * deltaTime;
	}
	else
	{
		velocity.x -= velocity.x * decelerationRate * deltaTime;
		velocity.y -= velocity.y * decelerationRate * deltaTime;
	}

	if (Vector2Length(velocity) > maxSpeed)
		velocity = Vector2Scale(Vector2Normalize(velocity), maxSpeed);

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (position.x > GetScreenWidth()) position.x = 0;
	if (position.x < 0) position.x = (float)GetScreenWidth();
	if (position.y > GetScreenHeight()) position.y = 0;
	if (position.y < 0) position.y = (float)GetScreenHeight();

	bulletTimer += deltaTime;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && bulletTimer >= bulletCooldown)
	{
		Shoot();
		bulletTimer = 0.0f;
	}

	for (int i = 0; i < maxBullets; i++)
		bullets[i].Update(deltaTime);
}

void Player::Draw()
{
	Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle dest = { position.x, position.y, (float)texture.width, (float)texture.height };
	Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };
	DrawTexturePro(texture, source, dest, origin, rotation + 90, WHITE);
	//DrawTexturePro(spriteSheet, frameRec,
		//{ animPosition.x, animPosition.y, (float)frameWidth, (float)frameHeight },
		//animOrigin, animRotation, WHITE);


	for (int i = 0; i < maxBullets; i++)
		bullets[i].Draw();
}
void Player::Shoot()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (!bullets[i].IsActive())
		{
			bullets[i].Fire(position, rotation, 800.0f);
			break;
		}
	}
}

void Player::LoseLife()
{
	lives--;
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	velocity = { 0.0f, 0.0f };
	rotation = 0.0f;
}

Vector2 Player::GetPosition() { return position; }
float Player::GetRadius() { return radius; }
Bullet* Player::GetBullets() { return bullets; }
int Player::GetMaxBullets() { return maxBullets; }
int Player::GetLives() { return lives; }