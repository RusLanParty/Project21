#pragma once
#include <SFML/Graphics.hpp>
#include "FPSCounter.h"
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "EnemyFormation.h"
#include "ParticleEffects.h"
#include "FPSCounter.h"
#include <vector>
class Game 
{
public:
	Game(sf::RenderWindow* window);
	static sf::RenderWindow* GameWindow;
	static sf::Font* Font;	
	static sf::RenderTexture* renderTexture;
	static sf::RenderTexture* renderTexture1;
	static bool bloom;
	static bool isIntro;
private:	
	std::shared_ptr<EnemyFormation> formation;	
	std::vector<std::shared_ptr<Projectile>> projectiles;		
	sf::Clock clock;
	sf::Clock primaryFireTimer;
	sf::Clock secondaryFireTimer;	
	void intro(float deltaTime);
	void mouse(float deltaTime, sf::Event event);	
	void mainLoop();
	void handleInput(float deltaTime);
	void keyboard(float deltaTime, sf::Event event);
	void update(float deltaTime);
	void draw(float deltaTime);
	void dispose();
};
