#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Shaders.h"
#include "Settings.h"
#include "Bullet.h"
class Player 
{
public:
	Player(std::shared_ptr<sf::Vector2f> spawnPos);
	void updateMovement(float deltaTime);
	bool isHit(std::shared_ptr<Projectile> proj);
	bool isDead();
	void applyDamage(float damage);
	std::shared_ptr<Bullet> shoot(sf::Vector2f pos);
	void hide();
	void draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	void accelerate(sf::Vector2f& acc, float deltaTime);
	void decelerate(sf::Vector2f& dec, float deltaTime);
	std::shared_ptr<sf::Vector2f> getVelocity() const;
	sf::Vector2f getPositionM() const;
	void setPositionM(sf::Vector2f& pos);
private:
	std::shared_ptr<sf::Vector2f> velocity;
	std::shared_ptr<sf::Vector2f> acceleration;
	sf::Texture playerTexture;
	std::shared_ptr<sf::Sprite> player;
	float _health;
};