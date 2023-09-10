#include "Projectile.h"
#include "Game.h"

Projectile::Projectile():
	_lifeTime(5.0f),
	_damage(0),
	_type("null"),
	_team(-1)
{
	
}

void Projectile::updatePosition(float deltaTime)
{
	sf::Vector2f newPos(this->_projectile->getPosition().x + this->_velocity.x * Settings::getConversionFactor() * deltaTime, this->_projectile->getPosition().y + this->_velocity.y * Settings::getConversionFactor() * deltaTime);
	this->_projectile->setPosition(newPos);
	this->_lifeTime -= 1.0f * deltaTime;
}

void Projectile::draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture)
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

int Projectile::getTeam()
{
	return this->_team;
}

bool Projectile::isDead()
{
	return this->_lifeTime <= 0;
}

void Projectile::kill()
{
	this->_lifeTime = 0;
}

std::string Projectile::getType()
{
	return this->_type;
}

sf::Vector2f Projectile::getPositionM()
{
	return this->_projectile->getPosition() / Settings::getConversionFactor();
}

sf::FloatRect Projectile::getGlobalBounds()
{
	return this->_projectile->getGlobalBounds();
}
