#include "Menu.h"
bool Menu::_active = true;
std::vector<GameText> Menu::_texts;

void Menu::initMenu()
{
    // Title text
    float offsetY = Game::GameWindow->getSize().y / 8;
    sf::Vector2f titlePos(Game::GameWindow->getSize().x / 2, Game::GameWindow->getSize().y - 5 * offsetY);
    sf::Vector2f title1Pos(Game::GameWindow->getSize().x / 2, Game::GameWindow->getSize().y - 4 * offsetY);
    GameText title(titlePos, "UNTITLED GAME", 50, sf::Color::Cyan, Game::Font);
    GameText title1(title1Pos, "GITHUB.COM/RUSLANPARTY", 50, sf::Color::Cyan, Game::Font);
    _texts.push_back(title);
    _texts.push_back(title1);
    
}

void Menu::menuLoop(float deltaTime)
{
    handleInput();
    update(deltaTime);
    draw();
    dispose();
}

bool Menu::isActive()
{
    return _active;
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
            Menu::_active = false;
            Game::isIntro = true;
            // Spawn player in the center, hide cursor and start the game's main loop
            std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(Game::GameWindow->getSize().x / 2, Game::GameWindow->getSize().y + 1.5f * Settings::getConversionFactor());
            Player::load(playerSpawnPos);
        }
    }
}
void Menu::update(float deltaTime)
{
    ParticleEffects::update(deltaTime);
}
void Menu::dispose()
{
    // Dispose particles
    ParticleEffects::dispose();
}
void Menu::draw()
{
    Game::GameWindow->clear(sf::Color::Black);

   // Game::renderTexture->setActive(true);
    Game::renderTexture1->setActive(true);

    // Draw starfield
    Starfield::draw(Game::GameWindow, Game::renderTexture1);

    // Draw particles
    ParticleEffects::draw(Game::GameWindow, Game::renderTexture1);

    // Draw text
    for (auto& txt : _texts) 
    {
        if (Game::bloom) 
        {
            txt.draw(Game::renderTexture1);
        }
        else 
        {
            txt.draw(Game::GameWindow);
        }
    }
       
    // Apply bloom
    if (Game::bloom)
    {
        //shaders->applyBloom(renderTexture, GameWindow);
        Shaders::applyBloom(Game::renderTexture1, Game::GameWindow);
        //shaders->applyAddition(renderTexture, renderTexture1, GameWindow);
    }

    // Reset
    //Game::renderTexture->clear(sf::Color::Black);
    Game::renderTexture1->clear(sf::Color::Black);
    Game::renderTexture->setActive(false);
    Game::renderTexture1->setActive(false);

    //Display
    Game::GameWindow->display();
}

