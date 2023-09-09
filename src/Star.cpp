#include "Star.h"
#include "Settings.h"
#include <iostream>
#include <random>

Star::Star(sf::Vector2f& position, float radius, sf::Vector2f& velocity, sf::Color color) :
	speedUp(false)	
{
	_star.setRadius(radius * Settings::getConversionFactor());
	_star.setPointCount(15);
	this->setPositionFromMetersToPixels(position);
	_star.setFillColor(color);
	_velocity = velocity;
	_acceleration.x = 0.0f;
	_acceleration.y = 0.0f;
}
Star::Star(sf::Vector2f& position, float radius, sf::Color color, sf::Vector2f& acceleration) :
	speedUp(true)
{
	_star.setRadius(radius * Settings::getConversionFactor());
	_star.setPointCount(15);
	this->setPositionFromMetersToPixels(position);
	_star.setFillColor(color);
	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_acceleration = acceleration;
}

sf::Vector2f Star::getVelocity()
{
	return this->_velocity;
}

void Star::setVelocity(sf::Vector2f velocity)
{
	this->_velocity = velocity;
}

void Star::setPositionFromMetersToPixels(sf::Vector2f pos)
{
	this->_star.setPosition(pos * Settings::getConversionFactor());
}

sf::Vector2f Star::getPositionInMetersFromPixels()
{
	sf::Vector2f pos(this->_star.getPosition() / Settings::getConversionFactor());
	return pos;
}

void Star::move(sf::Vector2f vector)
{
	sf::Vector2f newPos = (this->getPositionInMetersFromPixels() + vector);
	this->setPositionFromMetersToPixels(newPos);
}

sf::Vector2f Star::getAcceleration()
{
	return sf::Vector2f(this->_acceleration);
}

bool Star::isDead(sf::RenderWindow* GameWindow)
{
	if (this->getPositionInMetersFromPixels().y > GameWindow->getSize().y / Settings::getConversionFactor() + 0.1f) 
	{
		return true;
	}

	return false;
}




