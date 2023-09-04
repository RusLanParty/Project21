#pragma once
#include "SFML/Graphics.hpp"

class Enemy 
{
public:
	Enemy(std::shared_ptr<sf::Vector2f> spawnPos);
	bool isDead();
	void draw(std::shared_ptr<sf::RenderWindow> GameWindow);
private:
	std::shared_ptr<sf::RectangleShape> _enemy;
	bool _isDead;
	float _health;
};