#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<sf::Vector2f> spawnPos)	
{
	_damage = 5.0f;
	_velocity = std::make_shared<sf::Vector2f>(0.0f, -15.0f);
	sf::Vector2f size(0.005f * Settings::getConversionFactor(), 0.1f * Settings::getConversionFactor());
	_projectile = std::make_shared<sf::RectangleShape>(size);
	_projectile->setFillColor(sf::Color::Yellow);
	_projectile->setOrigin(_projectile->getLocalBounds().getSize().x / 2, _projectile->getLocalBounds().getSize().y / 2);
	_projectile->setPosition(*spawnPos * Settings::getConversionFactor());
}
