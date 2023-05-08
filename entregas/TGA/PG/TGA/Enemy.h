#ifndef ENEMY_H
#define ENEMY_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "entity.h"
#include "sprite_renderer.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, unsigned int health);

	void Move(float dt);
	bool isAlive();
	void Draw(SpriteRenderer& renderer);
	void Update(SpriteRenderer& renderer);

};

#endif