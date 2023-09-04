#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
class Player 
{
public:
	Player(std::shared_ptr<sf::Vector2f> spawnPos);
	std::shared_ptr<sf::RectangleShape> _player;
	void updatePosition(std::shared_ptr<sf::Vector2f> position);
private:
};