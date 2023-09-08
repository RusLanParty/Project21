#include "Enemy.h"
#include "Settings.h"
#include "Game.h"
#include "ColorConverter.h"
#include <random>
#include <iostream>

float normalVal = 0.05f;
float minVal = 0.01f;
float valOffset = 1.5f;

Enemy::Enemy(sf::Vector2f& spawnPos, int type):		
	_shootTimer(0.0f),
	_canShootFlag(false)
{
	switch (type) 
	{
	case 0:
		_health = 50.0f;
		break;
	case 1:
		_health = 100.0f;
		break;
	case 2:
		_health = 250.0f;
		break;
	case 3:
		_health = 300.0f;
		break;
	}
	_shootThreshold = 5.0f;
	_velocity = std::make_shared<sf::Vector2f>(0.0f, 0.0f);
	sf::Vector2f size(0.4f * Settings::getConversionFactor(), 0.2f * Settings::getConversionFactor());
	_enemy = std::make_shared<sf::RectangleShape>(size);
	_enemy->setOrigin(_enemy->getLocalBounds().getSize().x / 2, _enemy->getLocalBounds().getSize().y / 2);

	this->_hue = this->_health;
	this->_sat = 1.0f;
	this->_val = normalVal;

	sf::Color color(ColorConverter::HSVtoRGB(this->_hue, this->_sat, this->_val));
	_enemy->setFillColor(color);
	_enemy->setPosition(spawnPos);
}


bool Enemy::isDead()
{
	return this->_health <= 0.0f;
}

void Enemy::draw(sf::RenderWindow* GameWindow)
{
	GameWindow->draw(*this->_enemy);	
}

void Enemy::draw(std::shared_ptr<sf::RenderTexture> renderTexture)
{
	renderTexture->draw(*this->_enemy);
	renderTexture->display();
}

void Enemy::applyDamage(int damage)
{
	// Apply damage
	this->_health -= damage;	

	// Change color
	//this->_val = this->_health / 400.0f;
	this->_hue = this->_health;	
}

bool Enemy::isHit(std::shared_ptr<Projectile> proj)
{
	return this->_enemy->getGlobalBounds().intersects(proj->getGlobalBounds());
}
bool Enemy::isHit(std::shared_ptr<Particle> particle)
{
	return this->_enemy->getGlobalBounds().intersects(particle->getBounds());
}

void Enemy::updateMovement(float deltaTime)
{
	// Move
	sf::Vector2f newPos(this->getPositionM() + *this->_velocity * deltaTime);
	this->setPositionM(newPos);

	// Shooting timer
	this->_shootTimer += deltaTime;

	if (this->_shootTimer >= this->_shootThreshold) 
	{
		this->_shootTimer = 0.0f;
		this->_canShootFlag = true;
		this->_shootThreshold = getRandomChance();
	}
	else { _canShootFlag = false; }

}

bool Enemy::touchedBounds()
{
	// Bounds
	if (this->getPositionM().x > Game::GameWindow->getSize().x / Settings::getConversionFactor() - this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor())
	{
		//sf::Vector2f pos(Game::GameWindow->getSize().x / Settings::getConversionFactor() - this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor(), this->getPositionM().y);
		//this->setPositionM(pos);
		return true;
	}
	else if (this->getPositionM().x < this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor())
	{
		//sf::Vector2f pos(this->_enemy->getLocalBounds().width / 2 / Settings::getConversionFactor(), this->getPositionM().y);
		//this->setPositionM(pos);
		return true;
	}
	return false;
}

void Enemy::invertXVelocity()
{
	this->_velocity->x *= -1;
}

void Enemy::invertYVelocity()
{
	this->_velocity->y *= -1;
}

bool Enemy::canShoot()
{
	return _canShootFlag;
}

sf::Color Enemy::getColor()
{
	float hue = this->_hue;
	float sat = this->_sat;
	float val = this->_val;
	return sf::Color(hue, sat, val);
}

std::shared_ptr<EnemyBullet> Enemy::shoot(sf::Vector2f pos)
{
	std::shared_ptr<EnemyBullet> bul = std::make_shared<EnemyBullet>(pos);
	return bul;
}

float Enemy::getRandomChance()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(10.0f , 50.0f);
	float randChance = dis(gen);
	return randChance;	
}

sf::Vector2f Enemy::getPositionM()
{
	return this->_enemy->getPosition() / Settings::getConversionFactor();
}

void Enemy::setPositionM(sf::Vector2f& position)
{
	this->_enemy->setPosition(position * Settings::getConversionFactor());
}

void Enemy::setVelocity(sf::Vector2f& velocity)
{
	*this->_velocity = velocity;
}


void Enemy::updateColor(float deltaTime)
{
	if (this->blinking) 
	{
		if (this->_val < normalVal)
		{
			this->_val += valOffset * deltaTime;
		}
		else if (this->_val > normalVal)
		{
			this->_val = normalVal;
			this->blinking = false;
		}
	}
	else if (this->flashing) 
	{
		if (this->_val > normalVal)
		{
			this->_val -= valOffset * deltaTime;
		}
		else if (this->_val <= normalVal)
		{
			this->_val = normalVal;
			this->flashing = false;
		}
	}
	

	sf::Color color(ColorConverter::HSVtoRGB(this->_hue, this->_sat, this->_val));
	this->_enemy->setFillColor(color);

}

void Enemy::blink()
{
	this->_val = 0.0f;
	this->blinking = true;
}

void Enemy::flash()
{
	this->_val = 1.0f;
	this->flashing = true;
}
