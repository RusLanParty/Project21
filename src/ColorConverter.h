#pragma once
#include "SFML/Graphics.hpp"
class ColorConverter 
{
public:
	static sf::Color RGBtoHSV(sf::Color color);
	static sf::Color HSVtoRGB(float hue, float saturation, float value);
	static sf::Color getRandomColor();
};