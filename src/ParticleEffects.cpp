#include "ParticleEffects.h"
#include "ColorConverter.h"
#include <random>

std::vector<std::shared_ptr<Particle>> ParticleEffects::_particles;

void ParticleEffects::createSparks(const sf::Vector2f& position, float radius, float hue, float sat, float val)
{
	int amount = 25;

	for (int i = 0; i < amount; i++) 
	{
		// Calculate the angle for each spark evenly distributed around a circle
		float angle = static_cast<float>(i) * (360 / static_cast<float>(amount));

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 1.0f;		
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, hue, 0.0f, val, lifeTime));
	}
}
void ParticleEffects::createSparks(const sf::Vector2f& position, float radius)
{
	int amount = 25;

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for each spark evenly distributed around a circle
		float angle = static_cast<float>(i) * (360 / static_cast<float>(amount));

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 1.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, 50.0f, 0.0f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createThrust(const sf::Vector2f& position, float radius)
{
	int amount = 10;

	for (int i = 0; i < amount; i++)
	{
		// Use a fixed angle of 90 degrees (straight downwards)
		float angleRadians = 90.0f * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle (straight downwards)
		float speed = getRandomSpeed(true);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 0.3f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.0f, 30.0f, 0.1f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createExplosion(const sf::Vector2f& position, float radius)
{
	int amount = 400;

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for each particle evenly distributed around a circle
		float angle = static_cast<float>(i) * (360 / static_cast<float>(amount));

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles				
		float lifeTime = 3.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.05f, 40.0f, 0.1f, 1.0f, lifeTime));
	}
}

void ParticleEffects::createExplosion(const sf::Vector2f& position, float radius, float hue, float sat, float val)
{
	int amount = 400;

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for each spark evenly distributed around a circle
		float angle = static_cast<float>(i) * (360 / static_cast<float>(amount));

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles
		float lifeTime = 3.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.05f, hue, 0.8f, val, lifeTime));
	}
}

void ParticleEffects::createRocketExplosion(const sf::Vector2f& position, float radius)
{
	int amount = 600;

	for (int i = 0; i < amount; i++)
	{
		// Calculate the angle for each particle evenly distributed around a circle
		float angle = static_cast<float>(i) * (360 / static_cast<float>(amount));

		// Convert the angle to radians
		float angleRadians = angle * 3.14159265359f / 180.0f;

		// Calculate the velocity vector based on the angle
		float speed = getRandomSpeed(false);
		sf::Vector2f velocity(std::cos(angleRadians) * speed, std::sin(angleRadians) * speed);

		// Add to _particles				
		float lifeTime = 4.0f;
		_particles.emplace_back(std::make_shared<Particle>(position, velocity, 0.08f, 60.0f, 0.0f, 1.0f, lifeTime));
	}
}

void ParticleEffects::update(float deltaTime)
{
	for (auto& particle : _particles) 
	{
		particle->update(deltaTime);		
	}
}

void ParticleEffects::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
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

float ParticleEffects::getRandomSpeed(bool highSpeedOnly)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	if (highSpeedOnly) 
	{
		std::uniform_real_distribution<float> dis(15.0f, 40.0f);
		float randSpeed = dis(gen);
		return randSpeed;;
	}
	else
	{
		std::uniform_real_distribution<float> dis(0.1f, 20.0f);
		float randSpeed = dis(gen);
		return randSpeed;;
	}
}
