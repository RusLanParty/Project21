#pragma once
#include "SFML/Graphics.hpp"
#include "Starfield.h"
#include "GameText.h"

class Menu 
{
public:
	static void initMenu();
	static void menuLoop(float deltaTime);	
	static bool isActive();	
private:
	static bool _active;
	static void handleInput();
	//static void mouse();
	static void keyboard(sf::Event event);
	static void update(float deltaTime);
	static void dispose();
	static void draw();
	static std::vector<GameText> _texts;
};