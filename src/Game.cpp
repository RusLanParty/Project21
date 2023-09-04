#include "FPSCounter.h"
#include "Game.h"
#include "Player.h"
bool Game::leftPressed = false;
bool Game::bloom = true;
float spawnDelay = 300.0f;

Game::Game(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font):
GameWindow(window),
Font(font),
fpsCounter(0.0f, 0.0f, 150.0f, 0.0f, font)
{
    // CONVERSION FACTOR (scale of the game)
    Settings::setConversionFactor(20.0f);

    // Create starfield
    stars = std::make_shared<Starfield>(GameWindow);

    // Temporary single enemy spawn on start up
    //std::shared_ptr<sf::Vector2f> spawnEnemyPos = std::make_shared<sf::Vector2f>(500.0f, 500.0f);
    //_enemies.push_back(std::make_shared<Enemy>(spawnEnemyPos));

    // Spawn player in the center, hide cursor and start the game's main loop
    curMousePosX = std::make_shared<sf::Vector2f>();
    std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(GameWindow->getSize().x / 2 , GameWindow->getSize().y - 0.2f * Settings::getConversionFactor());
    player = std::make_shared<Player>(playerSpawnPos);
    GameWindow->setMouseCursorVisible(false);
	mainLoop();
}

void Game::mainLoop()
{
    while (GameWindow->isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        handleInput(deltaTime);
        update(deltaTime);
        draw(deltaTime);
        dispose();
    }
}

void Game::mouse(float deltaTime, sf::Event event)
{
    if (event.type == event.MouseMoved) 
    {
        std::shared_ptr<sf::Vector2f> newPos = std::make_shared<sf::Vector2f>((float)sf::Mouse::getPosition().x, GameWindow->getSize().y - 0.2f * Settings::getConversionFactor());
        curMousePosX = newPos;
        mouseBounds();
    }
    if (event.type == event.MouseButtonPressed) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            spawnTimer.restart();
            leftPressed = true;
        }
    }
    if (event.type == event.MouseButtonReleased) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            spawnTimer.restart();
            leftPressed = false;
        }
    }
}

void Game::mouseBounds()
{
    if (curMousePosX->x > GameWindow->getSize().x - 0.25f * Settings::getConversionFactor())
    {
        curMousePosX->x = GameWindow->getSize().x - 0.25f * Settings::getConversionFactor();
    }
    else if (curMousePosX->x < 0.25f * Settings::getConversionFactor())
    {
       curMousePosX->x = 0.25f * Settings::getConversionFactor();
    }
}

void Game::handleInput(float deltaTime)
{
    // Check for events
    sf::Event event;
    while (GameWindow->pollEvent(event))
    {
        keyboard(deltaTime, event);
        mouse(deltaTime, event);
    }

    // Respond to events
    if (leftPressed && (spawnTimer.getElapsedTime().asMilliseconds() >= spawnDelay || spawnTimer.getElapsedTime().asMilliseconds() == 0))
    {
        _bullets.push_back(std::make_shared<Bullet>(std::make_shared<sf::Vector2f>(player->_player->getPosition())));    
        spawnTimer.restart();
    }
}

void Game::keyboard(float deltaTime, sf::Event event)
{
    if (event.type == event.KeyPressed) 
    {
        if (event.key.code == sf::Keyboard::Escape) 
        {
            std::cout << "Closed by user" << "\n";
            GameWindow->close();
        }
        else if (event.key.code == sf::Keyboard::B) 
        {
            bloom = !bloom;
        }
    }
}

void Game::update(float deltaTime)
{
    // Update starfield
    stars->updateStars(GameWindow, deltaTime);

    // Update player
    player->updatePosition(curMousePosX);

    // Update bullets
    for (auto& bulletPtr : _bullets) 
    {
        bulletPtr->updatePosition(deltaTime);
    }

    // Update FPS counter
    fpsCounter.displayFps(deltaTime);
}

void Game::draw(float deltaTime)
{
    GameWindow->clear(sf::Color::Black);

    // Draw starfield
    stars->draw(GameWindow);

    // Draw fps counter
    fpsCounter.draw(GameWindow);

    // Draw bullets
    for (auto& bulletPtr : _bullets)
    {
        bulletPtr->draw(GameWindow);
    }

    // Draw enemies
    for (auto& enemyPtr : _enemies) 
    {
        enemyPtr->draw(GameWindow);
    }

    // Draw player
    GameWindow->draw(*player->_player);

    GameWindow->display();
}

void Game::dispose()
{
    // Despawn bullets
    auto it = _bullets.begin();
    while (it != _bullets.end())
    {
        if ((*it)->isDead())
        {
            // Release ownership by resetting the shared_ptr (if you haven't already).
            (*it).reset();            

            // Remove the element from the vector and advance the iterator.
            it = _bullets.erase(it);
        }
        else
        {
            // Move to the next element.
            ++it;
        }
    }
}
