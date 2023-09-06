#pragma once
#include <SFML/Graphics.hpp>
#include "Shaders.h"
#include "Settings.h"
class Player 
{
public:
	Player(std::shared_ptr<sf::Vector2f> spawnPos);
	void updateMovement(float deltaTime);
	void draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	void accelerate(std::shared_ptr<sf::Vector2f> acc, float deltaTime);
	void decelerate(std::shared_ptr <sf::Vector2f> dec, float deltaTime);
	std::shared_ptr<sf::Vector2f> getVelocity() const;
	sf::Vector2f getPositionM() const;
	void setPositionM(sf::Vector2f& pos);
private:
	std::shared_ptr<sf::Vector2f> velocity;
	std::shared_ptr<sf::Vector2f> acceleration;
	sf::Texture player_ship;
	std::shared_ptr<sf::Sprite> player;
};