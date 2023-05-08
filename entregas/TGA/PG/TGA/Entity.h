#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class Entity {
public:
	glm::vec2		Position, Size, Velocity;
	unsigned int	Health;
	Texture2D		Sprite;

	Entity();
	Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health);

	virtual void Draw(SpriteRenderer& renderer);
};

#endif