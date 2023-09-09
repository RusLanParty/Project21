#include "Starfield.h"
#include <iostream>
#include <random>
uint32_t Starfield::_starsCount = 200;
std::vector<Star> Starfield::_starfield;

void Starfield::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
	if (Game::bloom) 
	{		
		for (auto& star : _starfield)
		{
			renderTexture->draw(star._star);
		}
		renderTexture->display();
	}
	else 
	{
		for (auto& star : _starfield)
		{
			GameWindow->draw(star._star);			
		}
	}
}

void Starfield::updateStars(sf::RenderWindow* GameWindow, float deltaTime)
{
	// Move stars
	for (auto& star : _starfield) 
	{
		if (star.speedUp) 
		{
			sf::Vector2f newVel(star.getVelocity() + star.getAcceleration() * deltaTime);
			star.setVelocity(newVel);
		}
		sf::Vector2f vector(star.getVelocity() * deltaTime);
		star.move(vector);
	}

	// Spawn new stars
	if (_starfield.size() < _starsCount) 
	{
		while (_starfield.size() < _starsCount) 
		{
			float radius = getRandomRadius();
			sf::Vector2f position = getRandomPositionOutOfBounds(GameWindow);
			sf::Vector2f velocity = getRandomVelocity();
			sf::Color color = getRandomColor();
			Star star(position, radius, velocity, color);
			_starfield.push_back(star);
		}
	}

	// Despawn old stars
	auto it = _starfield.begin();
	while (it != _starfield.end())
	{
		if ((it)->isDead(GameWindow))
		{
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
	return _starfield.size();
}

void Starfield::createStarfield(sf::RenderWindow* GameWindow)
{	
	for (uint32_t i = 0; i < _starsCount; i++) 
	{
		float radius = getRandomRadius();
		sf::Vector2f position = getRandomPosition(GameWindow);
		sf::Color color = getRandomColor();
		sf::Vector2f acceleration = getRandomAcceleration();
		Star star(position, radius, color, acceleration);
		_starfield.push_back(star);
	}
}

std::vector<Star> Starfield::getStars()
{
	return Starfield::_starfield;
}

sf::Vector2f Starfield::getRandomPosition(sf::RenderWindow* GameWindow)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0.0f, GameWindow->getSize().x / Settings::getConversionFactor());
	std::uniform_real_distribution<float> disY(0.0f, GameWindow->getSize().y / Settings::getConversionFactor());
	float randX = disX(gen);
	float randY = disY(gen);
	sf::Vector2f randPos(randX, randY);
	return randPos;
}

sf::Vector2f Starfield::getRandomPositionOutOfBounds(sf::RenderWindow* GameWindow)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0.0f, GameWindow->getSize().x / Settings::getConversionFactor());
	std::uniform_real_distribution<float> disY(-10.0f, -5.0f);
	float randX = disX(gen);
	float randY = disY(gen);
	sf::Vector2f randPos(randX, randY);
	return randPos;
}

sf::Vector2f Starfield::getRandomVelocity()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a distribution with a bias towards lower values
	std::uniform_real_distribution<float> distribution(1.0f, 4.0f);
	float randomValue = distribution(gen);

	// Adjust the distribution for bias
	float exponent = 20.0f; 
	sf::Vector2f randVel(0.0f, pow(randomValue, exponent));
	return randVel;
	
}
sf::Vector2f Starfield::getRandomAcceleration()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.4f, 1.1f);
	float randomValue = distribution(gen);

	// Adjust the distribution for bias
	float exponent = 20.0f;
	sf::Vector2f randAcc(0.0f, pow(randomValue, exponent));
	return randAcc;
}

float Starfield::getRandomRadius()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.01f, 0.02f);
	float randRad = dis(gen);
	return randRad;
}

sf::Color Starfield::getRandomColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis1(0.0f, 360.0f);
	std::uniform_real_distribution<float> dis2(0.01f, 0.4f);
	std::uniform_real_distribution<float> dis3(0.05f, 0.4f);
	float hue = dis1(gen);
	float sat = dis2(gen);
	float val = dis3(gen);
	sf::Color randColor = ColorConverter::HSVtoRGB(hue, sat, val);
	return randColor;
}

