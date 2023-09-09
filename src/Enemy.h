#pragma once
#include "SFML/Graphics.hpp"
#include "Projectile.h"
#include "EnemyBullet.h"
#include "Particle.h"

class Enemy 
{
public:
	Enemy(sf::Vector2f& spawnPos, int type);
	void updateColor(float deltaTime);
	void updateMovement(float deltaTime);
	bool isHit(std::shared_ptr<Projectile> proj);
	bool isHit(std::shared_ptr<Particle> particle);
	void setPositionM(sf::Vector2f& position);
	void setVelocity(sf::Vector2f& velocity);
	bool touchedBounds();
	bool isDead();
	void draw(sf::RenderWindow* GameWindow);
	void draw(std::shared_ptr<sf::RenderTexture> renderTexture);
	void applyDamage(int damage);
	sf::Vector2f getPositionM();
	void flash();
	void blink();
	void invertXVelocity();
	void invertYVelocity();
	bool canShoot();
	sf::Color getColor();
	std::shared_ptr<EnemyBullet> shoot(sf::Vector2f pos);
protected:
	float getRandomChance();
	bool _canShootFlag;
	float _shootTimer;
	float _shootThreshold;
	sf::Vector2f _velocity;
	sf::RectangleShape _enemy;		
	float _health;
	float _hue;
	float _sat;
	float _val;
	bool flashing;
	bool blinking;
};