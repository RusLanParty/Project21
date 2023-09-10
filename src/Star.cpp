#include "Star.h"
#include "Settings.h"
#include "Game.h"
#include <iostream>
#include <random>

Star::Star(sf::Vector2f& position, float radius, sf::Color color, sf::Vector2f& acceleration) :
	speedUp(true)
{
	this->_star.setRadius(radius);
	this->_star.setPointCount(15);
	this->setPositionFromMetersToPixels(position);
	this->_star.setFillColor(color);
	this->_velocity.x = 0.0f;
	this->_velocity.y = 0.0f;
	this->_acceleration = acceleration;
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

void Star::respawn(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Color color)
{
	this->_star.setRadius(radius);
	this->_star.setFillColor(color);
	this->setPositionFromMetersToPixels(position);
	this->setVelocity(velocity);
}

bool Star::isDead()
{
	if (this->getPositionInMetersFromPixels().y > Game::GameWindow->getSize().y / Settings::getConversionFactor() + 0.1f) 
	{
		return true;
	}
	return false;
}




