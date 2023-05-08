#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool uniqueVAO = false);
	void UpdateSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size);
private:
	Shader       shader;
	unsigned int quadVAO;

	void initRenderData();
};

#endif