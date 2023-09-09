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
	int getTeam();
	bool isDead();
	void kill();
	std::string getType();
	sf::Vector2f getPositionM();
	sf::FloatRect getGlobalBounds();
protected:
	std::shared_ptr<sf::Shape> _projectile;
	sf::Vector2f _velocity;
	float _lifeTime;
	int _damage;
	int _team;
	std::string _type;
	
};