#pragma once
#include "SFML/Graphics.hpp"
#include "Starfield.h"
#include "GameText.h"

class Menu 
{
public:
	static void initMenu();
	static void menuLoop();	
	static bool isActive();	
private:
	static bool _active;
	static void handleInput();
	//static void mouse();
	static void keyboard(sf::Event event);
	//static void update();
	static void draw();
	static std::vector<GameText> _texts;
};