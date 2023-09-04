#include "Player.h"

Player::Player(std::shared_ptr<sf::Vector2f> spawnPos)
{
	sf::Vector2f size(8.0f * Settings::getConversionFactor(), 1.0f * Settings::getConversionFactor());
	_player = std::make_shared<sf::RectangleShape>(size);
	_player->setOrigin(_player->getLocalBounds().getSize().x / 2, _player->getLocalBounds().getSize().y / 2);
	_player->setPosition(*spawnPos);
}

void Player::updatePosition(std::shared_ptr<sf::Vector2f> position)
{
	this->_player->setPosition(*position);
}
