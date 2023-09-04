#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<sf::Vector2f> spawnPos):
	_lifeTime(5.0f)
{
	_velocity = std::make_shared<sf::Vector2f>(0.0f, -150.0f);
	sf::Vector2f size(0.2f * Settings::getConversionFactor(), 0.6f * Settings::getConversionFactor());
	_bullet = std::make_shared<sf::RectangleShape>(size);
	_bullet->setOrigin(_bullet->getLocalBounds().getSize().x / 2, _bullet->getLocalBounds().getSize().y / 2);
	_bullet->setPosition(*spawnPos);
}

void Bullet::updatePosition(float deltaTime)
{
	std::shared_ptr<sf::Vector2f> newPos = std::make_shared<sf::Vector2f>(this->_bullet->getPosition().x + this->_velocity->x * Settings::getConversionFactor() * deltaTime, this->_bullet->getPosition().y + this->_velocity->y * Settings::getConversionFactor() * deltaTime);
	this->_bullet->setPosition(*newPos);
	this->_lifeTime -= 1.0f * deltaTime;
}

void Bullet::draw(std::shared_ptr<sf::RenderWindow> GameWindow)
{
	GameWindow->draw(*this->_bullet);
}

bool Bullet::isDead()
{
	return this->_lifeTime <= 0;
}
