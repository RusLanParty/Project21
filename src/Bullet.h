#pragma once
#include "Projectile.h"
class Bullet : public Projectile
{
public:
	Bullet(std::shared_ptr<sf::Vector2f> spawnPos);
};
