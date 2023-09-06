#pragma once
#include "Enemy.h"
class EnemyFormation 
{
public:
	EnemyFormation();
	void checkProjectileCollision(std::shared_ptr<Projectile> proj);
	void updateFormation(float deltaTime);
	void draw(sf::RenderWindow* GameWindow);
	void despawnDead();
private:
	std::vector<std::vector<int>> _formationLayout;
	std::vector<std::shared_ptr<Enemy>> _enemies;
};