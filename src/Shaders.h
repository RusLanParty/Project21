#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
class Shaders 
{
public:
	static void loadShaders();
	static void applyBloom(std::shared_ptr<sf::RenderTexture> renderTexture, sf::RenderWindow* GameWindow);
	static void applyAddition(std::shared_ptr<sf::RenderTexture> renderTexture, std::shared_ptr<sf::RenderTexture> renderTexture1, sf::RenderWindow* GameWindow);
private:
	
	static sf::Shader bloomX;
	static sf::Shader bloomY;
	static sf::Shader add;
};