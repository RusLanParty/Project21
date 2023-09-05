#pragma once
#include "SFML/Graphics.hpp"
#include "Shaders.h"
#include "Star.h"
#include <vector>
class Starfield 
{
public:
	Starfield(std::shared_ptr<sf::RenderWindow> GameWindow);
	void draw(std::shared_ptr<sf::RenderWindow> GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	uint32_t getCurrentStarsCount();
	void updateStars(std::shared_ptr<sf::RenderWindow> GameWindow, float deltaTime);
private:		
	static uint32_t _starsCount;
	std::vector<std::shared_ptr<Star>> _starfield;
	void createStarfield(std::shared_ptr<sf::RenderWindow> GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomPosition(std::shared_ptr<sf::RenderWindow> GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomPositionOutOfBounds(std::shared_ptr<sf::RenderWindow> GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomVelocity();
	std::shared_ptr<sf::Vector2f> getRandomAcceleration();
	float getRandomRadius();	
	sf::Color getRandomColor();
	sf::Color HSVtoRGB(float hue, float saturation, float value);
};