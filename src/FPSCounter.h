#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class FPSCounter 
{
public:
	static void init(float x, float y, float z, float w, sf::Font* font);
	static void draw(sf::RenderWindow* window);
	static void update(float deltaTime);
	static void displayOjbectCount(int objCount);
private:
	static sf::Text _fpsText;
	static sf::Text _objectsText;
	static sf::Clock _clock;
	static int _frameCounter;
	static float _deltaFrames;
	static int _frameCounter1;
	static float _deltaFrames1;
	static void updateColor(float fps, float deltaTime);
	static void normalizeHSV();
	static sf::Color HSVtoRGB(float h, float s, float v);
	static int _hue;
	static float _sat;
	static float _val;
	static int _colorTransitionSpeed;
};