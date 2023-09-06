#pragma once
#include "SFML/Graphics.hpp"
class Star 
{
public:
	Star(std::shared_ptr<sf::Vector2f> position, float radius, std::shared_ptr<sf::Vector2f> velocity, sf::Color color);
	Star(std::shared_ptr<sf::Vector2f> position, float radius, sf::Color color, std::shared_ptr<sf::Vector2f> acceleration);
	std::shared_ptr<sf::Vector2f> getVelocity();
	void setVelocity(std::shared_ptr<sf::Vector2f> velocity);
	void setPositionFromMetersToPixels(std::shared_ptr<sf::Vector2f> pos);
	std::shared_ptr<sf::Vector2f> getPositionInMetersFromPixels();
	void move(std::shared_ptr<sf::Vector2f> vector);
	std::shared_ptr<sf::Vector2f> getAcceleration();
	bool isDead(sf::RenderWindow* GameWindow);
	std::shared_ptr<sf::CircleShape> _star;
	bool speedUp;
private:
	std::shared_ptr<sf::Vector2f> _velocity;
	std::shared_ptr <sf::Vector2f> _acceleration;
};