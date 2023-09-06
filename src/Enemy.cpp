#include "Enemy.h"
#include "Settings.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f& spawnPos):	
	_health(30.0f)
{
	_velocity = std::make_shared<sf::Vector2f>(3.0f, 0.0f);
	sf::Vector2f size(0.4f * Settings::getConversionFactor(), 0.2f * Settings::getConversionFactor());
	_enemy = std::make_shared<sf::RectangleShape>(size);
	_enemy->setOrigin(_enemy->getLocalBounds().getSize().x / 2, _enemy->getLocalBounds().getSize().y / 2);
	_enemy->setPosition(spawnPos);
}


bool Enemy::isDead()
{
	return this->_health <= 0.0f;
}

void Enemy::draw(sf::RenderWindow* GameWindow)
{
	GameWindow->draw(*this->_enemy);	
}

void Enemy::applyDamage(int damage)
{
	// Apply damage
	this->_health -= damage;	

	// Add explosion
}

bool Enemy::isHit(std::shared_ptr<Projectile> proj)
{
	return this->_enemy->getGlobalBounds().intersects(proj->_projectile->getGlobalBounds());
}

void Enemy::updateMovement(float deltaTime)
{
	sf::Vector2f newPos(this->getPositionM() + *this->_velocity * deltaTime);
	this->setPositionM(newPos);

	// Bounds
	if (this->getPositionM().x > Game::GameWindow->getSize().x / Settings::getConversionFactor() - this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor())
	{
		sf::Vector2f pos(Game::GameWindow->getSize().x / Settings::getConversionFactor() - this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor(), this->getPositionM().y + 1.0f);
		this->setPositionM(pos);
		this->invertXVelocity();
	}
	else if (this->getPositionM().x < this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor()) 
	{
		sf::Vector2f pos(this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor(), this->getPositionM().y + 1.0f);
		this->setPositionM(pos);
		this->invertXVelocity();
	}
}

void Enemy::invertXVelocity()
{
	this->_velocity->x *= -1;
}

void Enemy::invertYVelocity()
{
	this->_velocity->y *= -1;
}

sf::Vector2f Enemy::getPositionM()
{
	return this->_enemy->getPosition() / Settings::getConversionFactor();
}

void Enemy::setPositionM(sf::Vector2f& position)
{
	this->_enemy->setPosition(position * Settings::getConversionFactor());
}
