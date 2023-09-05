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
	static std::shared_ptr<sf::RenderWindow> GameWindow;
	std::shared_ptr<sf::Font> Font;	
	static bool bloom;
	std::shared_ptr<Shaders> shaders;
	std::shared_ptr<sf::RenderTexture> renderTexture;
private:	
	FPSCounter fpsCounter;
	std::shared_ptr<Starfield> stars;
	std::vector<std::shared_ptr<Bullet>> _bullets;
	std::vector <std::shared_ptr<Enemy>> _enemies;
	std::shared_ptr<Player> player;
	sf::Clock clock;
	sf::Clock spawnTimer;
	void mouse(float deltaTime, sf::Event event);	
	void mainLoop();
	void handleInput(float deltaTime);
	void keyboard(float deltaTime, sf::Event event);
	void update(float deltaTime);
	void draw(float deltaTime);
	void dispose();
	static bool lefMousePressed;	
	static bool keyPressedD;
	static bool keyPressedA;
};
