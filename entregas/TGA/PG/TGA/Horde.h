#ifndef HORDE_H
#define HORDE_H

#include <vector>
#include "Sprite_Renderer.h"
#include "enemy.h"

class Horde {
public:
	std::vector<Enemy> Enemies;

	Horde() {}

	void Populate(const char* file);
	void Prepare(std::vector<unsigned int> hordeData);
	void Attack(SpriteRenderer& renderer);
	bool IsDefeated();
};

#endif