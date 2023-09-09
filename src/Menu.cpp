#include "Menu.h"
bool Menu::active = true;


void Menu::menuLoop()
{
    handleInput();
    //update();
    draw();
}

bool Menu::isActive()
{
    return active;
}

void Menu::handleInput()
{
    // Check for events
    sf::Event event;
    while (Game::GameWindow->pollEvent(event))
    {
        keyboard(event);
        //mouse(deltaTime, event);
    }
}

void Menu::keyboard(sf::Event event)
{
    if (event.type == event.KeyPressed)
    {
        // Exit
        if (event.key.code == sf::Keyboard::Escape)
        {
            Game::GameWindow->close();
            //delete GameWindow;            
        }

        // Toggle bloom shader
        else if (event.key.code == sf::Keyboard::B)
        {
            Game::bloom = !Game::bloom;
        }

        // Enter game
        else if (event.key.code == sf::Keyboard::Enter)
        {
            //LOAD LEVEL
            Menu::active = false;
            Game::isIntro = true;
            // Spawn player in the center, hide cursor and start the game's main loop
            std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(Game::GameWindow->getSize().x / 2, Game::GameWindow->getSize().y + 1.5f * Settings::getConversionFactor());
            Player::load(playerSpawnPos);
        }
    }
}
void Menu::draw()
{
    Game::GameWindow->clear(sf::Color::Black);

    Game::renderTexture->setActive(true);
    Game::renderTexture1->setActive(true);

    // Draw starfield
    Starfield::draw(Game::GameWindow, Game::renderTexture1);

    // Draw particles
    ParticleEffects::draw(Game::GameWindow, Game::renderTexture1);

       
    // Apply bloom
    if (Game::bloom)
    {
        //shaders->applyBloom(renderTexture, GameWindow);
        Shaders::applyBloom(Game::renderTexture1, Game::GameWindow);
        //shaders->applyAddition(renderTexture, renderTexture1, GameWindow);
    }

    // Reset
    Game::renderTexture->clear(sf::Color::Black);
    Game::renderTexture1->clear(sf::Color::Black);
    Game::renderTexture->setActive(false);
    Game::renderTexture1->setActive(false);

    //Display
    Game::GameWindow->display();
}

