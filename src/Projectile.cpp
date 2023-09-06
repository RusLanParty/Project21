#include "Projectile.h"
#include "Game.h"

Projectile::Projectile():
	_lifeTime(5.0f),
	_damage(0)
{
	
}

void Projectile::updatePosition(float deltaTime)
{
	std::shared_ptr<sf::Vector2f> newPos = std::make_shared<sf::Vector2f>(this->_projectile->getPosition().x + this->_velocity->x * Settings::getConversionFactor() * deltaTime, this->_projectile->getPosition().y + this->_velocity->y * Settings::getConversionFactor() * deltaTime);
	this->_projectile->setPosition(*newPos);
	this->_lifeTime -= 1.0f * deltaTime;
}

void Projectile::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{	
	if (Game::bloom) 
	{
		renderTexture->draw(*this->_projectile);
		renderTexture->display();
	}
	else
	{
		GameWindow->draw(*this->_projectile);
	}
}

int Projectile::getDamage()
{
	return this->_damage;
}

bool Projectile::isDead()
{
	return this->_lifeTime <= 0;
}

void Projectile::kill()
{
	this->_lifeTime = 0;
}
