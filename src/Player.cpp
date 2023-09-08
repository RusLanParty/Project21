#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Game.h"
#include <iostream>
float maxAcc = 20.0f;
float maxSpeed = 10.0f;

Player::Player(std::shared_ptr<sf::Vector2f> spawnPos):
	_health(300.0f)
{
	// Player sprite
	player = std::make_shared<sf::Sprite>();

	// Velocity & acceleration vectors
	velocity = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
	acceleration = std::make_shared<sf::Vector2f>(0.0f, -1.0f);

	// Load player texture
	if (!playerTexture.loadFromFile("Assets/player.png"))
	{
		std::cout << "PLAYER: ERROR LOADING PLAYER.PNG" << "\n";
	}
	else 
	{
		std::cout << "PLAYER: PLAYER.PNG - SUCCESS" << "\n";
	}
	player->setTexture(playerTexture);
	player->setRotation(270.0f);
	player->setScale(0.35f, 0.35f);
	player->setOrigin(player->getLocalBounds().getSize().x / 2, player->getLocalBounds().getSize().y / 2);
	player->setPosition(*spawnPos);	

	// Darken texture
	sf::Color darkColor(40.0f, 40.0f, 40.0f);
	player->setColor(darkColor);
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
	}
	else if (this->getPositionM().x < this->player->getLocalBounds().width * 0.1f / conv)
	{
		sf::Vector2f pos(this->player->getLocalBounds().width * 0.1f / conv, this->player->getPosition().y / conv);
		this->setPositionM(pos);
		this->velocity->x = 0.0f;
		this->acceleration->x = 0.0f;
	}	
	this->acceleration->x = 0.0f;
}

bool Player::isHit(std::shared_ptr<Projectile> proj)
{
	return this->player->getGlobalBounds().intersects(proj->getGlobalBounds());
}

bool Player::isDead()
{
	return this->_health <= 0.0f;
}

void Player::applyDamage(float damage)
{
	this->_health -= damage;
}

std::shared_ptr<Bullet> Player::shoot(sf::Vector2f pos)
{
	std::shared_ptr<Bullet> bul = std::make_shared<Bullet>(pos);
	return bul;	
}

void Player::hide()
{
	this->player->setColor(sf::Color::Transparent);
}

void Player::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
	if (Game::bloom)
	{		
		renderTexture->draw(*this->player);
		renderTexture->display();
	}
	else
	{
		GameWindow->draw(*this->player);
	}
}

void Player::accelerate(sf::Vector2f& acc, float deltaTime)
{	
	// Update acceleration
	*this->acceleration += acc;
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

void Player::decelerate(sf::Vector2f& dec, float deltaTime)
{
	this->acceleration->x = 0.0f;
	this->acceleration->y = 0.0f;

	// X deceleration
	if (this->velocity->x > 0.0f)
	{
		this->velocity->x -= dec.x * deltaTime;		

		if (this->velocity->x < 0.0f)
		{
			this->velocity->x = 0.0f;
		}
	}
	else if (this->velocity->x < 0.0f)
	{
		this->velocity->x += dec.x * deltaTime;
		if (this->velocity->x > 0.0f)
		{
			this->velocity->x = 0.0f;
		}
	}

	// Y deceleration
	if (this->velocity->y > 0.0f)
	{
		this->velocity->y -= dec.y * deltaTime;

		if (this->velocity->y < 0.0f)
		{
			this->velocity->y = 0.0f;
		}
	}
	else if (this->velocity->y < 0.0f)
	{
		this->velocity->y += dec.y * deltaTime;
		if (this->velocity->y > 0.0f)
		{
			this->velocity->y = 0.0f;
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
