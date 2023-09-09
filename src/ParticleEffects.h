#pragma once
#include "SFML/Graphics.hpp"
#include "Particle.h"
class ParticleEffects 
{
public:	
	static void createSparks(const sf::Vector2f& position, float radius, float hue, float sat, float val);
	static void createSparks(const sf::Vector2f& position, float radius);
	static void createThrust(const sf::Vector2f& position, float radius);
	static void createExplosion(const sf::Vector2f& position, float radius);
	static void createExplosion(const sf::Vector2f& position, float radius, float hue, float sat, float val);
	static void createRocketExplosion(const sf::Vector2f& position, float radius);

	static void update(float deltaTime);
	static void draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	static std::shared_ptr<std::vector<std::shared_ptr<Particle>>> getAllParticles();
	static void dispose();

	static float getRandomSpeed(bool highSpeedOnly);
private:
	static std::vector<std::shared_ptr<Particle>> _particles;
};