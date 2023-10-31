#pragma once
#include "SFML/Graphics.hpp"
#include "Projectile.h"
class Particle
{
public:
	Particle(const sf::Vector2f& position, const sf::Vector2f& velocity,float damage, float hue, float sat, float val, float lifeTime);
	void setPositionM(const sf::Vector2f position);
	sf::Vector2f getPositionM();
	float getRandomRadiusM();
	void update(float deltaTime);
	void kill();
	sf::FloatRect getBounds();
	float getDamage(float deltaTime);
	bool isDead();
	void draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture);
private:
	sf::Vector2f _velocity;
	sf::CircleShape _particle;
	float _lifeTime;
	float _hue;
	float _sat;
	float _val;
	float _damage;
	float _deathSpeed;
};