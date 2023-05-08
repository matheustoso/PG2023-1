#include "Player.h"

Player::Player()
	: Entity() { }

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health)
	: Entity(pos, size, sprite, velocity, health) { }

bool Player::isAlive()
{
	return this->Health > 0;
}

void Player::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, true);
}

void Player::Update(SpriteRenderer& renderer)
{
	renderer.UpdateSprite(this->Sprite, this->Position, this->Size);
}

