#include "Player.h"
#include "Game.h"
#include <iostream>
float maxAcc = 25.0f * Settings::getConversionFactor();
float maxSpeed = 1500.0f * Settings::getConversionFactor();

Player::Player(std::shared_ptr<sf::Vector2f> spawnPos)
{
	// Player sprite
	player = std::make_shared<sf::Sprite>();

	// Velocity & acceleration vectors
	velocity = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
	acceleration = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
	
	//renderTexture = std::make_shared<sf::RenderTexture>();
	//if (!renderTexture->create(GameWindow->getSize().x, GameWindow->getSize().y)) 
	//{
	//	std::cout << "PLAYER: FAILED TO CREATE RENDERTEXTURE" << "\n";
	//}

	// Load player texture
	if (!player_ship.loadFromFile("Assets/player.png"))
	{
		std::cout << "PLAYER: ERROR LOADING PLAYER.PNG" << "\n";
	}
	else 
	{
		std::cout << "PLAYER: PLAYER.PNG - SUCCESS" << "\n";
	}
	player->setTexture(player_ship);
	player->setRotation(270.0f);
	player->setScale(0.4f, 0.4f);
	player->setOrigin(player->getLocalBounds().getSize().x / 2, player->getLocalBounds().getSize().y / 2);
	player->setPosition(*spawnPos);	
	player->setColor(sf::Color::White);
}

void Player::updateMovement(float deltaTime)
{	
	// Set new position
	this->player->setPosition(this->player->getPosition() + *this->velocity * deltaTime);
	this->acceleration->x = 0.0f;

	// Check bounds
	if (this->player->getPosition().x > Game::GameWindow->getSize().x - this->player->getLocalBounds().width * 0.1f)
	{
		this->player->setPosition(Game::GameWindow->getSize().x - this->player->getLocalBounds().width * 0.1f, this->player->getPosition().y);
		this->velocity->x = 0.0f;
		this->acceleration->x = 0.0f;
	}
	else if (this->player->getPosition().x < this->player->getLocalBounds().width * 0.1f)
	{
		this->player->setPosition(this->player->getLocalBounds().width * 0.1f, this->player->getPosition().y);
		this->velocity->x = 0.0f;
		this->acceleration->x = 0.0f;
	}
}

void Player::draw(std::shared_ptr<sf::RenderWindow> GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
	//if (Game::bloom)
	//{
		//renderTexture->setActive(true);
		//renderTexture->draw(*this->player);
		//renderTexture->display();
	//}
	//else
	//{
		GameWindow->draw(*this->player);
	//}
}

void Player::accelerate(std::shared_ptr<sf::Vector2f> acc, float deltaTime)
{	
	*this->acceleration += *acc * deltaTime;
	if (this->acceleration->x > maxAcc || this->velocity->x > maxSpeed)
	{
		this->acceleration->x = maxAcc;
	}
	else if (this->acceleration->x < -maxAcc || this->velocity->x < -maxSpeed)
	{
		this->acceleration->x = -maxAcc;
	}
	*this->velocity += *acceleration;
	if (this->velocity->x > maxSpeed)
	{
		this->velocity->x = maxSpeed;
	}
	else if (this->velocity->x < -maxSpeed)
	{
		this->velocity->x = -maxSpeed;
	}
}

void Player::decelerate(std::shared_ptr<sf::Vector2f> dec, float deltaTime)
{
	if (this->velocity->x > 0.0f)
	{
		this->velocity->x -= dec->x * deltaTime;
		//std::cout << "VELOCITY: " << this->velocity->x << "\n";

		if (this->velocity->x < 0.0f)
		{
			this->velocity->x = 0.0f;
		}
	}
	else if (this->velocity->x < 0.0f)
	{
		this->velocity->x += dec->x * deltaTime;
		if (this->velocity->x > 0.0f)
		{
			this->velocity->x = 0.0f;
		}
	}
}

std::shared_ptr<sf::Vector2f> Player::getVelocity()
{
	return this->velocity;
}
