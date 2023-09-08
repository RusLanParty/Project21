#include "Particle.h"
#include "Settings.h"
#include "Game.h"
#include "ColorConverter.h"
#include <random>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, float damage, float hue, float sat, float val, float lifeTime) :
	_lifeTime(lifeTime)
{	
	// Random radius
	float radius = getRandomRadiusM();

	// Damage
	_damage = damage;

	// Create shape
	_particle = std::make_shared<sf::CircleShape>(radius, 4);
	
	// Set HSV variables
	this->_hue = hue;
	this->_sat = sat;
	this->_val = val;

	this->setPositionM(position);
	this->_velocity = std::make_shared<sf::Vector2f>(velocity);
}

void Particle::setPositionM(const sf::Vector2f position)
{
	this->_particle->setPosition(position * Settings::getConversionFactor());
}

sf::Vector2f Particle::getPositionM()
{
	return this->_particle->getPosition() / Settings::getConversionFactor();
}

void Particle::update(float deltaTime)
{	
	// Update position
	sf::Vector2f newPos(this->getPositionM() + *this->_velocity * deltaTime);
	this->setPositionM(newPos);

	// Update lifetime and opacity
	float delta = std::sqrt(this->_velocity->x * this->_velocity->x + this->_velocity->y * this->_velocity->y);
	this->_lifeTime -= deltaTime * (delta + 0.5f);	
	this->_val = this->_lifeTime + 0.3f;

	// Particle radius decrease
	float newRad = this->_particle->getRadius() - 2 * deltaTime;

	// Decrease velocity
	float minSpeed = 0.04f * Settings::getConversionFactor();
	float decayFactor = 0.15f * Settings::getConversionFactor(); 
	sf::Vector2f currentVelocity = *this->_velocity;
	float currentSpeed = delta;
	if (currentSpeed > minSpeed) 
	{
		*this->_velocity *= std::pow(decayFactor, deltaTime);
	}	

	// Clamp the radius
	if (newRad <= 0.001f) 
	{
		newRad = 0.001f;
	}
	this->_particle->setRadius(newRad);

	// Darken color
	if (this->_hue > 15.0f) 
	{
		_hue -= 30 * delta * deltaTime;
	}

	// Increase saturation
	if (this->_sat < 0.5f)
	{
		_sat += delta * deltaTime;		
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
	this->_particle->setFillColor(ColorConverter::HSVtoRGB(this->_hue, this->_sat, this->_val));
}

void Particle::kill()
{
	this->_lifeTime = 0.0f;
}

sf::FloatRect Particle::getBounds()
{
	return this->_particle->getGlobalBounds();
}

float Particle::getDamage(float deltaTime)
{
	float delta = std::sqrt(this->_velocity->x * this->_velocity->x + this->_velocity->y * this->_velocity->y);
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
	std::uniform_real_distribution<float> dis(0.02f * Settings::getConversionFactor(), 0.06f * Settings::getConversionFactor());
	float randRad = dis(gen);
	return randRad;
}

void Particle::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
	if (Game::bloom)
	{
		renderTexture->draw(*this->_particle);
		renderTexture->display();
	}
	else
	{
		GameWindow->draw(*this->_particle);
	}
}
