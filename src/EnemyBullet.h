#pragma once
#include "Projectile.h"

class EnemyBullet : public Projectile 
{
public:
	EnemyBullet(sf::Vector2f spawnPos);
};