#include "Rocket.h"
#include "ColorConverter.h"

Rocket::Rocket(sf::Vector2f spawnPos) 
{
	_lifeTime = 5.0f;
	_type = "Rocket";
	_team = 0;
	_damage = 50.0f;
	_velocity.x = 0.0f;
	_velocity.y = -30.0f;
	sf::Vector2f size(0.1f * Settings::getConversionFactor(), 0.25f * Settings::getConversionFactor());
	_projectile = std::make_shared<sf::RectangleShape>(size);

	// Color
	sf::Color color(ColorConverter::HSVtoRGB(100.0f, 1.0f, 1.0f));
	_projectile->setFillColor(color);
	_projectile->setOrigin(_projectile->getLocalBounds().getSize().x / 2, _projectile->getLocalBounds().getSize().y / 2);
	_projectile->setPosition(spawnPos * Settings::getConversionFactor());
}