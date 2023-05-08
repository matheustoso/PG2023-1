#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Horde.h"

enum State {
	MENU,
	GAME,
	END,
	DEATH
};

const glm::vec2 PROJECTILE_VELOCITY(500.0f, 0.0f);
const glm::vec2 PROJECTILE_SIZE(30.0f, 10.0f);

const glm::vec2 PLAYER_SIZE(50.0f, 50.0f);
const glm::vec2 PLAYER_VELOCITY(175.0f, 175.0f);
const unsigned int PLAYER_HEALTH(3);

const float ATTACK_COOLDOWN(0.5f);
const float HIT_COOLDOWN(1.0f);


class Game {
public:
	State				State;
	bool				Keys[1024];
	bool				KeysProcessed[1024];
	unsigned int		Width, Height;
	std::vector<Horde>	Levels;
	unsigned int		Level;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt, float currentTime);
	void Update(float dt, float currentTime);
	void Render();
	void DoCollisions(float currentTime);
	bool CheckCollision(Entity& a, Entity& b);
	void ResetLevel();
	void ResetPlayer();
};

#endif
