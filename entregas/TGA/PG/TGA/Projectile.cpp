#include "projectile.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D sprite)
	: Entity(pos, size, sprite, velocity, 0), Size(size), Held(true) { }

glm::vec2 Projectile::Shoot(float dt, unsigned int window_width, Player rogue)
{
	if (!this->Held)
	{
		this->Position += this->Velocity * dt;

		if (this->Position.x <= 0.0f)
		{
			Reset(rogue);
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			Reset(rogue);
		}
	}
	return this->Position;
}


void Projectile::Reset(Player rogue)
{
	this->Position = rogue.Position + glm::vec2(rogue.Size.x / 2.0f + this->Size.x / 2.2f, rogue.Size.y / 2.0f);
	this->Held = true;
}