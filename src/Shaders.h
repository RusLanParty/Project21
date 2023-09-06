#pragma once
#include "SFML/Graphics.hpp"
class Shaders 
{
public:
	Shaders(sf::RenderWindow* GameWindow);
	void applyBloom(std::shared_ptr<sf::RenderTexture> renderTexture, sf::RenderWindow* GameWindow);
private:	
	sf::Shader bloomX;
	sf::Shader bloomY;
	sf::Shader add;
};