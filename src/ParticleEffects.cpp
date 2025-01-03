#include "ParticleEffects.h"
#include "ColorConverter.h"
#include <random>

std::vector<std::shared_ptr<Particle>> ParticleEffects::_particles;

void ParticleEffects::createSparks(const sf::Vector2f& position, float radius, float hue, float sat, float val)
{
	int amount = 50;

	float angleIncrement = 360.0f / static_cast<float>(amount);

	for (int i = 0; i < amount; i++) 
	{
		// Random angle from 0 to 360
		float angle = i * angleIncrement;

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 60.0f;		
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, hue, 0.0f, 1.0f, lifeTime));
	}
}
void ParticleEffects::createSparks(const sf::Vector2f& position, float radius)
{
	int amount = 50;

	float angleIncrement = 360.0f / static_cast<float>(amount);

	for (int i = 0; i < amount; i++)
	{
		// Random angle from 0 to -180
		float angle = i * angleIncrement / -2.0f;

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 60.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, 20.0f, 0.0f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createThrust(const sf::Vector2f& position, float radius)
{
	int amount = 20;

	for (int i = 0; i < amount; i++)
	{
		// Use a fixed angle of 90 degrees (straight downwards)
		float angleRadians = 90.0f * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle (straight downwards)
		float speed = getRandomSpeed(true);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 7.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, 15.0f, 0.6f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createExplosion(const sf::Vector2f& position, float radius)
{
	int amount = 200;

	float angleIncrement = 360.0f / static_cast<float>(amount);

	for (int i = 0; i < amount; i++)
	{
		// Random angle from 0 to 360
		float angle = i * angleIncrement;

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles				
		float lifeTime = 100.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.05f, 30.0f, 0.0f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createExplosion(const sf::Vector2f& position, float radius, float hue, float sat, float val)
{
	int amount = 200;

	float angleIncrement = 360.0f / static_cast<float>(amount);

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for this particle
		float angle = i * angleIncrement;

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 100.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.05f, hue, sat, 1.0f, lifeTime));
	}
}

void ParticleEffects::createRocketExplosion(const sf::Vector2f& position, float radius)
{
	int amount = 650;

	float angleIncrement = 360.0f / static_cast<float>(amount);

	for (int i = 0; i < amount; i++)
	{
		// Random angle from 0 to 360		
		float angle = i * angleIncrement;

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles				
		float lifeTime = 200.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 1.0f, 30.0f, 0.0f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createFireflies(const sf::Vector2f& position, float radius)
{
	int amount = 10;

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for each spark evenly distributed around a circle
		float angle = getRandomAngle();

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Generate random color
		sf::Color randCol(ColorConverter::getRandomColor());
		
		// Add to _particles
		float lifeTime = 1.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, 250.0f, randCol.g, 1.0f, lifeTime));
	}
}

void ParticleEffects::update(float deltaTime)
{
	for (auto& particle : _particles) 
	{
		particle->update(deltaTime);		
	}
}

void ParticleEffects::draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture)
{
	for (auto& particle : _particles) 
	{
		particle->draw(GameWindow, renderTexture);
	}
}

std::shared_ptr<std::vector<std::shared_ptr<Particle>>> ParticleEffects::getAllParticles()
{
	std::shared_ptr<std::vector<std::shared_ptr<Particle>>> particles = std::make_shared < std::vector<std::shared_ptr<Particle>>>(_particles);
	return particles;
}

void ParticleEffects::dispose()
{
	auto it = _particles.begin();
	while (it != _particles.end())
	{
		if ((*it)->isDead())
		{
			(*it).reset();
			it = _particles.erase(it);
		}
		else
		{			
			++it;
		}
	}
}

float ParticleEffects::getRandomAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0, 360.0f);	
	float angle = dis(gen);	
	return angle;
}

float ParticleEffects::getRandomSpeed(bool highSpeedOnly)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	if (highSpeedOnly) 
	{
		std::uniform_real_distribution<float> dis(15.0f, 20.0f);
		float randSpeed = dis(gen);
		return randSpeed;;
	}
	else
	{
		std::uniform_real_distribution<float> dis(0.01f, 20.0f);
		float randSpeed = dis(gen);
		return randSpeed;;
	}
}
