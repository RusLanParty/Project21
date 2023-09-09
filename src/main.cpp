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
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        sf::ContextSettings settings;
        settings.antialiasingLevel = 16;
        
        // Aspect ratio 16:9
        float targetAspectRatio = 16.0f / 9.0f;

        float actualAspectRatio = static_cast<float>(desktopMode.width) / desktopMode.height;

        // Create the game window with the calculated height
        sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(desktopMode.width, desktopMode.height), "PROJECT21", sf::Style::Fullscreen, settings);

        window->setFramerateLimit(144);
        window->setVerticalSyncEnabled(true);

        // If the actual aspect ratio is different, adjust the view to fit the entire game world
        if (actualAspectRatio != targetAspectRatio)
        {

            // Create a view with the game's default aspect ratio
            sf::View gameView(sf::FloatRect(0, 0, targetAspectRatio * desktopMode.height, desktopMode.height));

            float scale = actualAspectRatio / targetAspectRatio;
            gameView.setSize(targetAspectRatio * desktopMode.height * scale, desktopMode.height * scale);
            gameView.setCenter(desktopMode.width / 2, desktopMode.height / 2);

            // Set the view for rendering
            window->setView(gameView);
        }

        Game game(window, font);
    }
}   
int main()
{
    start();
    return 0;
}