#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
class Shaders 
{
public:
	static void loadShaders();
	static void applyBloom(sf::RenderTexture*, sf::RenderWindow* GameWindow);
	static void applyAddition(sf::RenderTexture* renderTexture, sf::RenderTexture* renderTexture1, sf::RenderWindow* GameWindow);
private:
	
	static sf::Shader bloomX;
	static sf::Shader bloomY;
	static sf::Shader add;
};