#include "entity.h"


Entity::Entity()
	: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(1.0f, 0.0f), Sprite(), Health(1) { }

Entity::Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health)
	: Position(pos), Size(size), Velocity(velocity), Sprite(sprite), Health(health) { }

void Entity::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size);
}