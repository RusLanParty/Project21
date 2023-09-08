#include "EnemyBullet.h"
#include "ColorConverter.h"

EnemyBullet::EnemyBullet(sf::Vector2f spawnPos)
{
	_team = 1;
	_damage = 10.0f;
	_velocity = std::make_shared<sf::Vector2f>(0.0f, 7.0f);
	sf::Vector2f size(0.03f * Settings::getConversionFactor(), 0.1f * Settings::getConversionFactor());
	_projectile = std::make_shared<sf::RectangleShape>(size);

	// Color
	sf::Color color(ColorConverter::HSVtoRGB(200.0f, 1.0f, 1.0f));
	_projectile->setFillColor(color);
	_projectile->setOrigin(_projectile->getLocalBounds().getSize().x / 2, _projectile->getLocalBounds().getSize().y / 2);
	_projectile->setPosition(spawnPos * Settings::getConversionFactor());
}
