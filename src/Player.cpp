#include "Player.h"
#include "Game.h"
#include <iostream>
float maxAcc = 20.0f;
float maxSpeed = 10.0f;

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
	player->setScale(0.35f, 0.35f);
	player->setOrigin(player->getLocalBounds().getSize().x / 2, player->getLocalBounds().getSize().y / 2);
	player->setPosition(*spawnPos);	
	player->setColor(sf::Color::White);
}

void Player::updateMovement(float deltaTime)
{	
	// Conversion pixels/meters
	float conv = Settings::getConversionFactor();

	// Set new position
	sf::Vector2f newPos(this->getPositionM() + *this->velocity * deltaTime);
	this->setPositionM(newPos);

	// Check bounds
	if (this->getPositionM().x > Game::GameWindow->getSize().x / conv  - this->player->getLocalBounds().width * 0.1f / conv)
	{
		sf::Vector2f pos(Game::GameWindow->getSize().x / conv - this->player->getLocalBounds().width * 0.1f / conv, this->player->getPosition().y / conv);
		this->setPositionM(pos);
		this->velocity->x = 0.0f;
		this->acceleration->x = 0.0f;
	}
	else if (this->getPositionM().x < this->player->getLocalBounds().width * 0.1f / conv)
	{
		sf::Vector2f pos(this->player->getLocalBounds().width * 0.1f / conv, this->player->getPosition().y / conv);
		this->setPositionM(pos);
		this->velocity->x = 0.0f;
		this->acceleration->x = 0.0f;
	}	
}

void Player::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
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
	// Update acceleration
	*this->acceleration += *acc;
	if (this->acceleration->x > maxAcc)
	{
		this->acceleration->x = maxAcc;
	}
	else if (this->acceleration->x < -maxAcc)
	{
		this->acceleration->x = -maxAcc;
	}

	// Update velocity
	*this->velocity += *acceleration * deltaTime;
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
	this->acceleration->x = 0.0f;

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

std::shared_ptr<sf::Vector2f> Player::getVelocity() const
{
	return this->velocity;
}

sf::Vector2f Player::getPositionM() const
{
	return this->player->getPosition() / Settings::getConversionFactor();
}

void Player::setPositionM(sf::Vector2f& pos)
{
	this->player->setPosition(pos * Settings::getConversionFactor());
}
