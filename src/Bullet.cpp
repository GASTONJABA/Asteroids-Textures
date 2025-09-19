#include "Bullet.h"
#include <math.h>

Bullet::Bullet()
{
	position = { 0, 0 };
	velocity = { 0, 0 };
	radius = 3.0f;
	active = false;
}

void Bullet::Fire(Vector2 startPos, float rotation, float speed)
{
	position = startPos;
	velocity.x = cosf(DEG2RAD * rotation) * speed;
	velocity.y = sinf(DEG2RAD * rotation) * speed;
	active = true;
}

void Bullet::Update(float deltaTime)
{
	if (!active) return;

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	if (position.x < 0 || position.x > GetScreenWidth() ||
		position.y < 0 || position.y > GetScreenHeight())
	{
		active = false;
	}
}

void Bullet::Draw()
{
	if (active)
		DrawCircleV(position, radius, WHITE);
}

Vector2 Bullet::GetPosition()
{
	return position;
}

float Bullet::GetRadius()
{
	return radius;
}


bool Bullet::IsActive()
{
	return active;
}

void Bullet::Deactivate()
{
	active = false;
}
