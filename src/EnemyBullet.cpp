#include "EnemyBullet.h"
#include "ColorConverter.h"

EnemyBullet::EnemyBullet(sf::Vector2f spawnPos)
{
	_type = "Bullet";
	_team = 1;
	_damage = 0.0f;
	_velocity.x = 0.0f;
	_velocity.y = 10.0f;
	sf::Vector2f size(0.08f * Settings::getConversionFactor(), 0.2f * Settings::getConversionFactor());
	_projectile = std::make_shared<sf::RectangleShape>(size);

	// Color
	sf::Color color(ColorConverter::HSVtoRGB(215.0f, 1.0f, 1.0f));
	_projectile->setFillColor(color);
	_projectile->setOrigin(_projectile->getLocalBounds().getSize().x / 2, _projectile->getLocalBounds().getSize().y / 2);
	_projectile->setPosition(spawnPos * Settings::getConversionFactor());
}
