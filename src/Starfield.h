#pragma once
#include "SFML/Graphics.hpp"
#include "Shaders.h"
#include "Star.h"
#include <vector>
class Starfield 
{
public:
	Starfield(sf::RenderWindow* GameWindow);
	void draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture);
	uint32_t getCurrentStarsCount();
	void updateStars(sf::RenderWindow* GameWindow, float deltaTime);
private:		
	static uint32_t _starsCount;
	std::vector<std::shared_ptr<Star>> _starfield;
	void createStarfield(sf::RenderWindow* GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomPosition(sf::RenderWindow* GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomPositionOutOfBounds(sf::RenderWindow* GameWindow);
	std::shared_ptr <sf::Vector2f> getRandomVelocity();
	std::shared_ptr<sf::Vector2f> getRandomAcceleration();
	float getRandomRadius();	
	sf::Color getRandomColor();
	sf::Color HSVtoRGB(float hue, float saturation, float value);
};