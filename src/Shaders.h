#pragma once
#include "SFML/Graphics.hpp"
class Shaders 
{
public:
	Shaders(sf::RenderWindow* window);
	void applyBloom(std::shared_ptr<sf::RenderTexture> renderTexture, sf::RenderWindow* GameWindow);
	void applyAddition(std::shared_ptr<sf::RenderTexture> renderTexture, std::shared_ptr<sf::RenderTexture> renderTexture1, sf::RenderWindow* GameWindow);
private:
	
	sf::Shader bloomX;
	sf::Shader bloomY;
	sf::Shader add;
};