#include "Starfield.h"
#include "Settings.h"
#include "Star.h"
#include "Game.h"
#include "SFML/Graphics/Shader.hpp"
#include <iostream>
#include <random>
uint32_t Starfield::_starsCount = 500;
Starfield::Starfield(std::shared_ptr<sf::RenderWindow> GameWindow)
{	

	createStarfield(GameWindow);
}

void Starfield::draw(std::shared_ptr<sf::RenderWindow> GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
	if (Game::bloom) 
	{		
		for (auto& star : _starfield)
		{
			renderTexture->draw(*star->_star);
		}
		renderTexture->display();
	}
	else 
	{
		for (auto& star : _starfield)
		{
			GameWindow->draw(*star->_star);			
		}
	}
}

void Starfield::updateStars(std::shared_ptr<sf::RenderWindow> GameWindow, float deltaTime)
{
	// Move stars
	for (auto& star : _starfield) 
	{
		if (star->speedUp) 
		{
			std::shared_ptr<sf::Vector2f> newVel = std::make_shared<sf::Vector2f>(*star->getVelocity() + *star->getAcceleration() * deltaTime);
			star->setVelocity(newVel);
		}
		std::shared_ptr<sf::Vector2f> vector = std::make_shared<sf::Vector2f>(*star->getVelocity() * deltaTime);
		star->move(vector);
	}

	// Spawn new stars
	if (_starfield.size() < _starsCount) 
	{
		while (_starfield.size() < _starsCount) 
		{
			float radius = getRandomRadius();
			std::shared_ptr<sf::Vector2f> position = getRandomPositionOutOfBounds(GameWindow);
			std::shared_ptr<sf::Vector2f> velocity = getRandomVelocity();
			sf::Color color = getRandomColor();
			std::shared_ptr<Star> star = std::make_shared<Star>(position, radius, velocity, color);
			_starfield.push_back(star);
		}
	}

	// Despawn old stars
	auto it = _starfield.begin();
	while (it != _starfield.end())
	{
		if ((*it)->isDead(GameWindow))
		{
			(*it).reset();

			it = _starfield.erase(it);
		}
		else
		{
			++it;
		}
	}
}

uint32_t Starfield::getCurrentStarsCount()
{
	return this->_starfield.size();
}

void Starfield::createStarfield(std::shared_ptr<sf::RenderWindow> GameWindow)
{
	for (uint32_t i = 0; i < _starsCount; i++) 
	{
		float radius = getRandomRadius();
		std::shared_ptr<sf::Vector2f> position = getRandomPosition(GameWindow);
		sf::Color color = getRandomColor();
		std::shared_ptr<sf::Vector2f> acceleration = getRandomAcceleration();
		std::shared_ptr<Star> star = std::make_shared<Star>(position, radius, color, acceleration);
		_starfield.push_back(star);
	}
}

std::shared_ptr<sf::Vector2f> Starfield::getRandomPosition(std::shared_ptr<sf::RenderWindow> GameWindow)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0.0f, GameWindow->getSize().x / Settings::getConversionFactor());
	std::uniform_real_distribution<float> disY(0.0f, GameWindow->getSize().y / Settings::getConversionFactor());
	float randX = disX(gen);
	float randY = disY(gen);
	std::shared_ptr<sf::Vector2f> randPos = std::make_shared<sf::Vector2f>(randX, randY);
	return randPos;
}

std::shared_ptr<sf::Vector2f> Starfield::getRandomPositionOutOfBounds(std::shared_ptr<sf::RenderWindow> GameWindow)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0.0f, GameWindow->getSize().x / Settings::getConversionFactor());
	std::uniform_real_distribution<float> disY(-10.0f, -5.0f);
	float randX = disX(gen);
	float randY = disY(gen);
	std::shared_ptr<sf::Vector2f> randPos = std::make_shared<sf::Vector2f>(randX, randY);
	return randPos;
}

std::shared_ptr<sf::Vector2f> Starfield::getRandomVelocity()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a distribution with a bias towards lower values
	std::uniform_real_distribution<float> distribution(1.0f, 4.0f);
	float randomValue = distribution(gen);

	// Adjust the distribution for bias
	float exponent = 20.0f; 
	std::shared_ptr<sf::Vector2f> randVel = std::make_shared<sf::Vector2f>(0.0f, pow(randomValue, exponent));
	return randVel;
	
}
std::shared_ptr<sf::Vector2f> Starfield::getRandomAcceleration()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.4f, 1.1f);
	float randomValue = distribution(gen);

	// Adjust the distribution for bias
	float exponent = 20.0f;
	std::shared_ptr<sf::Vector2f> randAcc = std::make_shared<sf::Vector2f>(0.0f, pow(randomValue, exponent));
	return randAcc;
}

float Starfield::getRandomRadius()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.05f, 0.2f);
	float randRad = dis(gen);
	return randRad;
}

sf::Color Starfield::getRandomColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis1(0.0f, 360.0f);
	std::uniform_real_distribution<float> dis2(0.01f, 0.7f);
	std::uniform_real_distribution<float> dis3(0.01f, 0.5f);
	float hue = dis1(gen);
	float sat = dis2(gen);
	float val = dis3(gen);
	sf::Color randColor = HSVtoRGB(hue, sat, val);
	return randColor;
}

sf::Color Starfield::HSVtoRGB(float hue, float saturation, float value)
{

	int hi = int(hue / 60.0f) % 6;
	float f = hue / 60.0f - int(hue / 60.0f);
	float p = value * (1 - saturation);
	float q = value * (1 - f * saturation);
	float t = value * (1 - (1 - f) * saturation);

	switch (hi) {
	case 0:
		return sf::Color(value * 255, t * 255, p * 255);
	case 1:
		return sf::Color(q * 255, value * 255, p * 255);
	case 2:
		return sf::Color(p * 255, value * 255, t * 255);
	case 3:
		return sf::Color(p * 255, q * 255, value * 255);
	case 4:
		return sf::Color(t * 255, p * 255, value * 255);
	default: // case 5:
		return sf::Color(value * 255, p * 255, q * 255);
	}
}
