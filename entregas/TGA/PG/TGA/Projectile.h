#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "entity.h"
#include "texture.h"
#include "Player.h"

class Projectile : public Entity
{
public:
	glm::vec2 Size;
	bool      Held;

	Projectile(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Shoot(float dt, unsigned int window_width, Player rogue);
	void      Reset(Player rogue);
};

#endif