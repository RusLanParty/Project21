#include "Enemy.h"
#include "Settings.h"
#include <iostream>

Enemy::Enemy(std::shared_ptr<sf::Vector2f> spawnPos):
	_isDead(false),
	_health(100.0f)
{
	sf::Vector2f size(0.4f * Settings::getConversionFactor(), 0.2f * Settings::getConversionFactor());
	_enemy = std::make_shared<sf::RectangleShape>(size);
	_enemy->setOrigin(_enemy->getLocalBounds().getSize().x / 2, _enemy->getLocalBounds().getSize().y / 2);
	_enemy->setPosition(*spawnPos);
}

bool Enemy::isDead()
{
	return this->_isDead;
}

void Enemy::draw(std::shared_ptr<sf::RenderWindow> GameWindow)
{
	GameWindow->draw(*this->_enemy);
}
