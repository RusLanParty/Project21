#pragma once
#include "SFML/Graphics.hpp"
class Star 
{
public:	
	Star(sf::Vector2f& position, float radius, sf::Color color, sf::Vector2f& acceleration);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);
	void setPositionFromMetersToPixels(sf::Vector2f pos);
	sf::Vector2f getPositionInMetersFromPixels();
	void move(sf::Vector2f vector);
	sf::Vector2f getAcceleration();
	void respawn(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
	bool isDead();
	bool speedUp;
	sf::CircleShape _star;
private:
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
};