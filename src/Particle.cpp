#include "Particle.h"
#include "Settings.h"
#include "Game.h"
#include "ColorConverter.h"
#include <random>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, float damage, float hue, float sat, float val, float lifeTime) :
	_lifeTime(lifeTime),	
	_hue(hue),
	_sat(sat),
	_val(val),
	_damage(damage)
{	
	// Random radius
	float radius = getRandomRadiusM();


	// Create shape
	this->_particle.setRadius(radius);

	// Set point count
	this->_particle.setPointCount(4);
	
	// Set position
	this->setPositionM(position);

	// Set velocity
	this->_velocity = velocity;
}

void Particle::setPositionM(const sf::Vector2f position)
{
	this->_particle.setPosition(position * Settings::getConversionFactor());
}

sf::Vector2f Particle::getPositionM()
{
	return this->_particle.getPosition() / Settings::getConversionFactor();
}

void Particle::update(float deltaTime)
{	
	sf::Vector2f currentVelocity = this->_velocity;
	float currentSpeed = std::sqrt(this->_velocity.x * this->_velocity.x + this->_velocity.y * this->_velocity.y);

	// Update position
	sf::Vector2f newPos(this->getPositionM() + this->_velocity * deltaTime);
	this->setPositionM(newPos);

	// Update lifetime and opacity
	this->_lifeTime= _lifeTime - 0.7 - currentSpeed / 8;	
	this->_val -= 0.0f;

	// Decrease velocity
	float minSpeed = 0.01f * Settings::getConversionFactor();
	float decayFactor = 0.99f;  
		
	if (currentSpeed > minSpeed)
	{
		this->_velocity *= decayFactor;
	}

	// Particle radius decrease		
	float newRadius = this->_particle.getRadius() - (0.01f * Settings::getConversionFactor() * deltaTime) - (0.025f * currentSpeed);
	if (newRadius < 0.01f * Settings::getConversionFactor())
	{
		newRadius = 0.01f * Settings::getConversionFactor();
	}
	else if (newRadius > 0.18f * Settings::getConversionFactor())
	{
		newRadius = 0.18f * Settings::getConversionFactor();
	}
	this->_particle.setRadius(newRadius);

	// Increase saturation
	if (this->_sat < 0.7f)
	{
		_sat += (currentSpeed) * deltaTime;		
	}

	if (this->_hue > 0.0f) 
	{
		this->_hue -= 2.0f;
	}

	// Clamp value
	if (this->_val < 0.0f) 
	{
		_val = 0.0f;
	}
	else if (this->_val > 1.0f) 
	{
		this->_val = 1.0f;
	}

	// Clamp saturation
	if (this->_sat < 0.0f) 
	{
		this->_sat = 0.0f;
	}
	else if (this->_sat > 1.0f) 
	{
		this->_sat = 1.0f;
	}

	// Clamp hue
	if (this->_hue > 360.0f) 
	{
		_hue = 360.0f;
	}
	else if (this->_hue < 0.0f) 
	{		
		this->_hue = 0.0f;
	}

	// Set color
	this->_particle.setFillColor(ColorConverter::HSVtoRGB(this->_hue, this->_sat, this->_val));	
}

void Particle::kill()
{
	this->_lifeTime = 0.0f;
}

sf::FloatRect Particle::getBounds()
{
	return this->_particle.getGlobalBounds();
}

float Particle::getDamage(float deltaTime)
{
	float delta = std::sqrt(this->_velocity.x * this->_velocity.x + this->_velocity.y * this->_velocity.y);
	float dmg = this->_damage * delta;	
	
	return dmg;
}

bool Particle::isDead()
{
	return this->_lifeTime <= 0.0f;
}

float Particle::getRandomRadiusM()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.01f * Settings::getConversionFactor(), 0.9f * Settings::getConversionFactor());
	float randRad = dis(gen);
	return randRad;
}

void Particle::draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture)
{
	if (Game::bloom)
	{
		renderTexture->draw(this->_particle);
		renderTexture->display();				
	}
	else
	{
		GameWindow->draw(this->_particle);				
	}
}
