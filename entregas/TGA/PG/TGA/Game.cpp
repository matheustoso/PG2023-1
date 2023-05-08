#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "entity.h"
#include "horde.h"
#include "projectile.h"
#include "player.h"
#include "particle_generator.h"
#include "text_renderer.h"
#include <iostream>
#include <irrklang/irrKlang.h>
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();
TextRenderer* Text;
SpriteRenderer* Renderer;
ParticleGenerator* Particles;
Player* Rogue;
Projectile* Weapon;

float AttackTime = 0.0f;
float HitTime = 0.0f;

Game::Game(unsigned int width, unsigned int height)
	: State(MENU), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Rogue;
	delete Weapon;
	delete Particles;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("particle.vs", "particle.fs", nullptr, "particle");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetMatrix4("projection", projection);
	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);
	// load textures
	ResourceManager::LoadTexture("textures/backgrounds/dirt.jpg", false, "dirt");
	ResourceManager::LoadTexture("textures/backgrounds/grass.jpg", false, "grass");
	ResourceManager::LoadTexture("textures/backgrounds/stone.jpg", false, "stone");
	ResourceManager::LoadTexture("textures/backgrounds/dungeon.jpg", false, "dungeon");
	ResourceManager::LoadTexture("textures/particles/particle.png", true, "particle");
	ResourceManager::LoadTexture("textures/weapon/weapon.png", true, "weapon");
	ResourceManager::LoadTexture("textures/player/player.png", true, "player", 3, 4);
	ResourceManager::LoadTexture("textures/enemy/enemy.png", true, "enemy", 3, 4);
	// text 
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("fonts/ocraext.TTF", 24);
	// load levels
	Horde one;
	one.Populate("levels/one.lvl");
	this->Levels.push_back(one);
	Horde two;
	two.Populate("levels/two.lvl");
	this->Levels.push_back(two);
	Horde three;
	three.Populate("levels/three.lvl");
	this->Levels.push_back(three);
	Horde four;
	four.Populate("levels/four.lvl");
	this->Levels.push_back(four);
	this->Level = 0;
	// particles 
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 1500);
	// configure entities
	glm::vec2 playerPos(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height / 2.0f - PLAYER_SIZE.y / 2.0f);
	glm::vec2 projectilePos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f + PROJECTILE_SIZE.x / 2.2f, PLAYER_SIZE.y / 2.0f);
	Rogue = new Player(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"), PLAYER_VELOCITY, PLAYER_HEALTH);
	Weapon = new Projectile(projectilePos, PROJECTILE_SIZE, PROJECTILE_VELOCITY, ResourceManager::GetTexture("weapon"));

}

void Game::Update(float dt, float currentTime)
{
	if (this->State == GAME) {
		this->DoCollisions(currentTime);
		Weapon->Shoot(dt, this->Width, *Rogue);
		Particles->Update(dt, *Weapon, 2, glm::vec2(Weapon->Size.x / 2.0f, Weapon->Size.y / 2.0f));
		Rogue->Update(*Renderer);
		for (Enemy& enemy : this->Levels[this->Level].Enemies) {
			enemy.Move(dt);
			enemy.Update(*Renderer);
		}
		if (!Rogue->isAlive()) {
			SoundEngine->stopAllSounds();
			SoundEngine->play2D("audio/sfx/death.mp3", false);
			this->ResetLevel();
			this->ResetPlayer();
			this->State = DEATH;
		}
	}
	if (this->State == GAME && this->Levels[this->Level].IsDefeated())
	{
		SoundEngine->stopAllSounds();
		SoundEngine->play2D("audio/sfx/end.mp3", false);
		this->ResetLevel();
		this->ResetPlayer();
		this->State = END;
	}
}

void Game::ProcessInput(float dt, float currentTime)
{
	if (this->State == MENU)
	{
		if (this->Keys[GLFW_KEY_SPACE] and !this->KeysProcessed[GLFW_KEY_SPACE]) {
			this->KeysProcessed[GLFW_KEY_SPACE] = true;
			this->State = GAME;
			SoundEngine->play2D("audio/soundtrack/Megalovania.mp3", true);
		}
		if (this->Keys[GLFW_KEY_D] and !this->KeysProcessed[GLFW_KEY_D]) {
			this->KeysProcessed[GLFW_KEY_D] = true;
			this->Level = (this->Level + 1) % 4;
		}
		if (this->Keys[GLFW_KEY_A] and !this->KeysProcessed[GLFW_KEY_A])
		{
			this->KeysProcessed[GLFW_KEY_A] = true;
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
		}
	}

	if (this->State == GAME)
	{
		float velocityX = PLAYER_VELOCITY.x * dt;
		float velocityY = PLAYER_VELOCITY.y * dt;

		if (this->Keys[GLFW_KEY_A])
		{
			if (Rogue->Position.x >= 0.0f) {
				Rogue->Position.x -= velocityX;
				Rogue->Sprite.iAnimation = 1;
				if (Weapon->Held) {
					Weapon->Position.x -= velocityX;
					Weapon->Velocity = -PROJECTILE_VELOCITY;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Rogue->Position.x <= this->Width - Rogue->Size.x) {
				Rogue->Position.x += velocityX;
				Rogue->Sprite.iAnimation = 2;
				if (Weapon->Held) {
					Weapon->Position.x += velocityX;
					Weapon->Velocity = PROJECTILE_VELOCITY;
				}
			}
		}
		if (this->Keys[GLFW_KEY_W])
		{
			if (Rogue->Position.y >= 0.0f) {
				Rogue->Position.y -= velocityY;
				Rogue->Sprite.iAnimation = 4;
				if (Weapon->Held) {
					Weapon->Position.y -= velocityY;
				}
			}
		}
		if (this->Keys[GLFW_KEY_S])
		{
			if (Rogue->Position.y <= this->Height - Rogue->Size.y) {
				Rogue->Position.y += velocityY;
				Rogue->Sprite.iAnimation = 0;
				if (Weapon->Held) {
					Weapon->Position.y += velocityY;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE] and currentTime > AttackTime + ATTACK_COOLDOWN and Weapon->Held and !this->KeysProcessed[GLFW_KEY_SPACE]) {
			this->KeysProcessed[GLFW_KEY_SPACE] = true;
			Weapon->Held = false;
			SoundEngine->play2D("audio/sfx/throw.mp3", false);
		}
	}

	if (this->State == END || this->State == DEATH)
	{
		if (this->Keys[GLFW_KEY_SPACE] and !this->KeysProcessed[GLFW_KEY_SPACE])
		{
			this->KeysProcessed[GLFW_KEY_SPACE] = true;
			this->State = MENU;
		}
	}
}

void Game::Render()
{

	Texture2D background;
	if (this->Level == 0)
		background = ResourceManager::GetTexture("dirt");
	else if (this->Level == 1)
		background = ResourceManager::GetTexture("grass");
	else if (this->Level == 2)
		background = ResourceManager::GetTexture("stone");
	else if (this->Level == 3)
		background = ResourceManager::GetTexture("dungeon");

	Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height));

	if (this->State == GAME) {
		this->Levels[this->Level].Attack(*Renderer);
		Rogue->Draw(*Renderer);
		Particles->Draw();
		Weapon->Draw(*Renderer);
		Text->RenderText("HP: " + std::to_string(Rogue->Health), 5.0f, 5.0f, 2.0f);
	}
	if (this->State == MENU)
	{
		Text->RenderText("Level " + std::to_string(this->Level + 1), 5.0f, this->Height - 50.0f, 2.0f, glm::vec3(0.9f, 0.7f, 0.15f));
		Text->RenderText("I N V A S I O N", 50.0f, this->Height / 2 - 80.0f, 3.0f, glm::vec3(0.5f, 0.0f, 0.0f));
		Text->RenderText("Press SPACE to start", 250.0f, this->Height / 2, 1.0f);
		Text->RenderText("Press A or D to select level", 245.0f, this->Height / 2 + 20.0f, 0.75f);
	}
	if (this->State == END)
	{
		Text->RenderText("HORDE DEFEATED", 270.0, this->Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0));
	}
	if (this->State == DEATH)
	{
		Text->RenderText("YOU DIED", 270.0, this->Height / 2 - 60.0, 2.0, glm::vec3(1.0, 0.0, 0.0));
	}
	if (this->State == END || this->State == DEATH)
	{
		Text->RenderText("Press SPACE to retry or ESC to quit", 130.0, this->Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0));
	}
}

void Game::DoCollisions(float currentTime)
{
	for (Enemy& enemy : this->Levels[this->Level].Enemies) {
		if (enemy.isAlive()) {
			if (CheckCollision(*Weapon, enemy) and currentTime > AttackTime + ATTACK_COOLDOWN) {
				enemy.Health -= 1;
				Weapon->Reset(*Rogue);
				AttackTime = currentTime;
				SoundEngine->play2D("audio/sfx/hit.mp3", false);
			}
			if (CheckCollision(*Rogue, enemy) and currentTime > HitTime + HIT_COOLDOWN) {
				if (Rogue->Health > 0) Rogue->Health -= 1;
				HitTime = currentTime;
				SoundEngine->play2D("audio/sfx/oof.mp3", false);
			}
		}
	}
}

bool Game::CheckCollision(Entity& a, Entity& b)
{
	bool collisionX = a.Position.x + a.Size.x >= b.Position.x &&
		b.Position.x + b.Size.x >= a.Position.x;

	bool collisionY = a.Position.y + a.Size.y >= b.Position.y &&
		b.Position.y + b.Size.y >= a.Position.y;

	return collisionX && collisionY;
}

void Game::ResetLevel() {
	if (this->Level == 0)
		this->Levels[0].Populate("levels/one.lvl");
	else if (this->Level == 1)
		this->Levels[1].Populate("levels/two.lvl");
	else if (this->Level == 2)
		this->Levels[2].Populate("levels/three.lvl");
	else if (this->Level == 3)
		this->Levels[3].Populate("levels/four.lvl");

	Rogue->Health = 3;
}

void Game::ResetPlayer() {
	Rogue->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height / 2.0f - PLAYER_SIZE.y / 2.0f);
	Weapon->Position = Rogue->Position + glm::vec2(PLAYER_SIZE.x / 2.0f + PROJECTILE_SIZE.x, PLAYER_SIZE.y / 2.0f - PROJECTILE_SIZE.y / 2.0f);
}
