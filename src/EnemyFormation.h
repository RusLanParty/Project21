#pragma once
#include "Enemy.h"
#include <queue>
class EnemyFormation 
{
public:
	EnemyFormation(std::shared_ptr<std::vector<std::vector<int>>> formationLayout);
	void checkProjectileCollision(std::shared_ptr<Projectile> proj);
	void checkParticleCollision(float deltaTime);
	void updateFormation(float deltaTime, std::vector<std::shared_ptr<Projectile>>* projectiles);
	void moveDown();
	void draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture);
    void despawnDead();
private:
	float _spawnThresh;
	float _spawnT;
	std::vector<std::shared_ptr<Enemy>> _enemies;	 
	std::queue<std::shared_ptr<Enemy>> _spawnQue;
};