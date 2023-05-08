#include "Horde.h"

#include "resource_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Horde::Populate(const char* file)
{
	this->Enemies.clear();
	unsigned int enemyCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<unsigned int> hordeData;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			while (sstream >> enemyCode)
				hordeData.push_back(enemyCode);
		}
		if (hordeData.size() > 0)
			this->Prepare(hordeData);
	}
}

void Horde::Prepare(std::vector<unsigned int> hordeData)
{
	srand(time(NULL));
	for (unsigned int& enemyHealth : hordeData) {
		glm::vec2 size(50.0f + (float)(enemyHealth * 2), 50.0f + (float)(enemyHealth * 2));
		glm::vec2 velocity(200.0f + rand() % 51, 0.0f);
		glm::vec2 pos(0.0f - size.x, 0.0f);

		int i = rand() % 2;
		if (i == 0) {
			pos.x = 800.0f + size.x;
			velocity.x = -velocity.x;
		}
		pos.y = (float)(rand() % (int)(600 - size.y));


		Enemy enemy(pos, size, ResourceManager::GetTexture("enemy"), velocity, enemyHealth);
		if (i == 0) enemy.Sprite.iAnimation = 1;
		else enemy.Sprite.iAnimation = 2;
		this->Enemies.push_back(enemy);
	}
}

void Horde::Attack(SpriteRenderer& renderer)
{
	for (Enemy& enemy : this->Enemies)
		if (enemy.Health > 0)
			enemy.Draw(renderer);

}

bool Horde::IsDefeated()
{
	for (Enemy& enemy : this->Enemies)
		if (enemy.Health > 0)
			return false;
	return true;
}
