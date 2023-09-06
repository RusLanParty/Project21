#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

void start() 
{
    static std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    if (!font->loadFromFile("Fonts/arial.ttf"))
    {
        std::cout << "Error loading font" << "\n";
    }
    else
    { 
        sf::ContextSettings settings;
        settings.antialiasingLevel = 16;
        sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "PROJECT21", sf::Style::Fullscreen, settings);
        window->setFramerateLimit(144);
        window->setVerticalSyncEnabled(true);
        Game game(window, font);
    }
}   
int main()
{
    start();
    return 0;
}