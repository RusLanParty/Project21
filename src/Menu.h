#pragma once
#include "SFML/Graphics.hpp"
#include "Starfield.h"
#include "Game.h"

class Menu 
{
public:
	static void menuLoop();	
	static bool isActive();	
private:
	static bool active;
	static void handleInput();
	//static void mouse();
	static void keyboard(sf::Event event);
	//static void update();
	static void draw();
};