#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "entity.h"
#include "sprite_renderer.h"

class Player : public Entity {
public:
	Player();
	Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health);

	bool isAlive();
	void Draw(SpriteRenderer& renderer);
	void Update(SpriteRenderer& renderer);
};

#endif