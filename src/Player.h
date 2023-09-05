#pragma once
#include <SFML/Graphics.hpp>
#include "Shaders.h"
#include "Settings.h"
class Player 
{
public:
	Player(std::shared_ptr<sf::Vector2f> spawnPos);
	void updateMovement(float deltaTime);
	std::shared_ptr<sf::Sprite> player;
	void draw(std::shared_ptr<sf::RenderWindow> GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	void accelerate(std::shared_ptr<sf::Vector2f> acc, float deltaTime);
	void decelerate(std::shared_ptr <sf::Vector2f> dec, float deltaTime);
	std::shared_ptr<sf::Vector2f> getVelocity();
private:
	std::shared_ptr<sf::Vector2f> velocity;
	std::shared_ptr<sf::Vector2f> acceleration;
	sf::Texture player_ship;
};