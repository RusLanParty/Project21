#pragma once
#include <SFML/Graphics.hpp>
#include "FPSCounter.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Starfield.h"
#include <vector>
class Game 
{
public:
	Game(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font);
	std::shared_ptr<sf::RenderWindow> GameWindow;
	std::shared_ptr<sf::Font> Font;
	std::shared_ptr<sf::Vector2f> curMousePosX;
	static bool bloom;
private:
	FPSCounter fpsCounter;
	std::shared_ptr<Starfield> stars;
	std::vector<std::shared_ptr<Bullet>> _bullets;
	std::vector <std::shared_ptr<Enemy>> _enemies;
	std::shared_ptr<Player> player;
	sf::Clock clock;
	sf::Clock spawnTimer;
	void mouse(float deltaTime, sf::Event event);
	void mouseBounds();
	void mainLoop();
	void handleInput(float deltaTime);
	void keyboard(float deltaTime, sf::Event event);
	void update(float deltaTime);
	void draw(float deltaTime);
	void dispose();
	static bool leftPressed;	
};
