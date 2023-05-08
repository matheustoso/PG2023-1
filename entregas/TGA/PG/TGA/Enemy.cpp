#include "Enemy.h"

Enemy::Enemy()
	: Entity() { }

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health)
	: Entity(pos, size, sprite, velocity, health) { }

void Enemy::Move(float dt)
{
	this->Position.x += this->Velocity.x * dt;
	if (this->Velocity.x > 0.0f and this->Position.x > 850.0f) {
		this->Position.y = (float)(rand() % (int)(600 - this->Size.y));
		this->Position.x = 0.0f - this->Size.x;
	}
	if (this->Velocity.x < 0.0f and this->Position.x < -50.0f) {
		this->Position.y = (float)(rand() % (int)(600 - this->Size.y));
		this->Position.x = 800.0f + this->Size.x;
	}
}

bool Enemy::isAlive()
{
	return this->Health > 0;
}

void Enemy::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, true);
}

void Enemy::Update(SpriteRenderer& renderer)
{
	renderer.UpdateSprite(this->Sprite, this->Position, this->Size);
}