#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Settings.h"

class Projectile 
{
public:
	Projectile();
	void updatePosition(float deltaTime);
	void draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	int getDamage();
	bool isDead();
	void kill();
	std::shared_ptr<sf::RectangleShape> _projectile;
protected:
	std::shared_ptr<sf::Vector2f> _velocity;
	float _lifeTime;
	int _damage;
	
};