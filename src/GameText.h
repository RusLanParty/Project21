#pragma once
#include "SFML/Graphics.hpp"

class GameText
{
public:
	GameText(sf::Vector2f position, std::string text, int size, sf::Color color, sf::Font* font);
	void draw(sf::RenderWindow* GameWindow);
	void draw(sf::RenderTexture* renderTexture);
private:
	sf::Text _text;
};
