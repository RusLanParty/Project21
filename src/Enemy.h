#pragma once
#include "SFML/Graphics.hpp"
#include "Projectile.h"

class Enemy 
{
public:
	Enemy(sf::Vector2f& spawnPos);
	bool isDead();
	void draw(sf::RenderWindow* GameWindow);
	void applyDamage(int damage);
	bool isHit(std::shared_ptr<Projectile> proj);
	void updateMovement(float deltaTime);
	void invertXVelocity();
	void invertYVelocity();
	sf::Vector2f getPositionM();
	void setPositionM(sf::Vector2f& position);
private:
	std::shared_ptr<sf::Vector2f> _velocity;
	std::shared_ptr<sf::RectangleShape> _enemy;	
	float _health;
};