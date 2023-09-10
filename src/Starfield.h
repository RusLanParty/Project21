#pragma once
#include "SFML/Graphics.hpp"
#include "Shaders.h"
#include "Star.h"
#include "ColorConverter.h"
#include "Settings.h"
#include <vector>
class Starfield 
{
public:	
	static void draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture);
	static uint32_t getCurrentStarsCount();
	static void updateStars(sf::RenderWindow* GameWindow, float deltaTime);
	static void createStarfield(sf::RenderWindow* GameWindow);
	static std::vector<Star> getStars();
private:		
	static uint32_t _starsCount;
	static std::vector<Star> _starfield;
	static sf::Vector2f getRandomPosition(sf::RenderWindow* GameWindow);
	static sf::Vector2f getRandomPositionOutOfBounds(sf::RenderWindow* GameWindow);
	static sf::Vector2f getRandomVelocity();
	static sf::Vector2f getRandomAcceleration();
	static float getRandomRadius();
	static sf::Color getRandomColor();	
};