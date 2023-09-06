#include "Star.h"
#include "Settings.h"
#include <iostream>
#include <random>

Star::Star(std::shared_ptr<sf::Vector2f> position, float radius, std::shared_ptr<sf::Vector2f> velocity, sf::Color color) :
	speedUp(false)	
{
	_star = std::make_shared<sf::CircleShape>(radius * Settings::getConversionFactor());
	_star->setPointCount(15);
	this->setPositionFromMetersToPixels(position);
	_star->setFillColor(color);
	_velocity = velocity;
	_acceleration = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
}
Star::Star(std::shared_ptr<sf::Vector2f> position, float radius, sf::Color color, std::shared_ptr<sf::Vector2f> acceleration) :
	speedUp(true)
{
	_star = std::make_shared<sf::CircleShape>(radius * Settings::getConversionFactor());
	_star->setPointCount(15);
	this->setPositionFromMetersToPixels(position);
	_star->setFillColor(color);
	_velocity = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
	_acceleration = std::make_shared<sf::Vector2f>(*acceleration);
}

std::shared_ptr<sf::Vector2f> Star::getVelocity()
{
	return this->_velocity;
}

void Star::setVelocity(std::shared_ptr<sf::Vector2f> velocity)
{
	this->_velocity = velocity;
}

void Star::setPositionFromMetersToPixels(std::shared_ptr<sf::Vector2f> pos)
{
	this->_star->setPosition(*pos * Settings::getConversionFactor());
}

std::shared_ptr<sf::Vector2f> Star::getPositionInMetersFromPixels()
{
	std::shared_ptr<sf::Vector2f> pos = std::make_shared<sf::Vector2f>(this->_star->getPosition() / Settings::getConversionFactor());
	return pos;
}

void Star::move(std::shared_ptr<sf::Vector2f> vector)
{
	std::shared_ptr<sf::Vector2f> newPos = std::make_shared <sf::Vector2f>(*this->getPositionInMetersFromPixels() + *vector);
	this->setPositionFromMetersToPixels(newPos);
}

std::shared_ptr<sf::Vector2f> Star::getAcceleration()
{
	return std::shared_ptr<sf::Vector2f>(this->_acceleration);
}

bool Star::isDead(sf::RenderWindow* GameWindow)
{
	if (this->getPositionInMetersFromPixels()->y > GameWindow->getSize().y / Settings::getConversionFactor() + 0.1f) 
	{
		return true;
	}
	return false;
}




