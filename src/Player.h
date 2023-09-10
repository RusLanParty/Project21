#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Shaders.h"
#include "Settings.h"
#include "Bullet.h"
#include "Rocket.h"
#include "Game.h"
#include <iostream>

class Player 
{
public:
	static void load(std::shared_ptr<sf::Vector2f> spawnPos);
	static void updateMovement(float deltaTime);
	static bool isHit(std::shared_ptr<Projectile> proj);
	static bool isDead();
	static void applyDamage(float damage);
	static std::shared_ptr<Bullet> shootPrimary(sf::Vector2f pos);
	static std::shared_ptr<Rocket> shootSecondary(sf::Vector2f pos);
	static void hide();
	static void draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture);
	static void accelerate(sf::Vector2f& acc, float deltaTime);
	static void decelerate(sf::Vector2f& dec, float deltaTime);
	static sf::Vector2f getVelocity();
	static sf::Vector2f getPositionM();
	static void setPositionM(sf::Vector2f& pos);
private:
	static sf::Vector2f velocity;
	static sf::Vector2f acceleration;
	static sf::Texture playerTexture;
	static sf::Sprite player;
	
};