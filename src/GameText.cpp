#include "GameText.h"

GameText::GameText(sf::Vector2f position, std::string text, int size, sf::Color color, sf::Font* font)
{
	this->_text.setFont(*font);
	this->_text.setString(text);
	this->_text.setCharacterSize(50);
	this->_text.setOrigin(this->_text.getLocalBounds().getSize().x / 2, this->_text.getLocalBounds().getSize().y / 2);
	this->_text.setFillColor(color);
	this->_text.setPosition(position);
}

void GameText::draw(sf::RenderWindow* GameWindow)
{
	GameWindow->draw(this->_text);
}

void GameText::draw(sf::RenderTexture* renderTexture)
{	
	renderTexture->draw(this->_text);
	renderTexture->display();
}
