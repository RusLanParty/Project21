#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Settings.h"

class Bullet 
{
public:
	Bullet(std::shared_ptr<sf::Vector2f> spawnPos);
	void updatePosition(float deltaTime);
	void draw(std::shared_ptr<sf::RenderWindow> GameWindow);
	bool isDead();
private:
	std::shared_ptr<sf::RectangleShape> _bullet;
	std::shared_ptr<sf::Vector2f> _velocity;
	float _lifeTime;
	
};