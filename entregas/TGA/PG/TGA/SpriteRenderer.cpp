#include "sprite_renderer.h"
#include "Resource_Manager.h"


SpriteRenderer::SpriteRenderer(Shader& shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool uniqueVAO)
{
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	if (!uniqueVAO) glBindVertexArray(this->quadVAO);
	else glBindVertexArray(texture.VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::UpdateSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size)
{
	//this->shader.Use();
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(position, 0.0f));

	//model = glm::scale(model, glm::vec3(size, 1.0f));

	//this->shader.SetMatrix4("model", model);

	texture.iFrame = (texture.iFrame + 1) % texture.nFrames;

	float offsetx = texture.iFrame * texture.dx;
	float offsety = texture.iAnimation * texture.dy;
	this->shader.SetVector2f("offsets", offsetx, offsety);
}

void SpriteRenderer::initRenderData()
{
	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}