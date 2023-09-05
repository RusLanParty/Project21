#include "FPSCounter.h"
#include "Game.h"
#include "Player.h"
bool Game::keyPressedA = false;
bool Game::keyPressedD = false;
bool Game::lefMousePressed = false;
bool Game::bloom = true;
std::shared_ptr <sf::RenderWindow> Game::GameWindow;
float rateOfFire = 150.0f;

Game::Game(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font):
Font(font),
fpsCounter(0.0f, 0.0f, 150.0f, 0.0f, font)
{
    GameWindow = window;
    // CONVERSION FACTOR (scale of the game)
    Settings::setConversionFactor(20.0f);

    // Temporary single enemy spawn on start up
    //std::shared_ptr<sf::Vector2f> spawnEnemyPos = std::make_shared<sf::Vector2f>(500.0f, 500.0f);
    //_enemies.push_back(std::make_shared<Enemy>(spawnEnemyPos));

    // Spawn player in the center, hide cursor and start the game's main loop
    std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(GameWindow->getSize().x / 2 , GameWindow->getSize().y - 10.0f * Settings::getConversionFactor());
    player = std::make_shared<Player>(playerSpawnPos);
    GameWindow->setMouseCursorVisible(false);

    // Init shaders
    shaders = std::make_shared<Shaders>(GameWindow);

    // Create starfield
    stars = std::make_shared<Starfield>(GameWindow);

    renderTexture = std::make_shared<sf::RenderTexture>();
    if (!renderTexture->create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "GAME: FAILED TO CREATE RENDER TEXTURE";
    }

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
    
    if (event.type == event.MouseButtonPressed) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            lefMousePressed = true;
        }
    }
    if (event.type == event.MouseButtonReleased) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            lefMousePressed = false;
        }
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
    // Shooting
    if (lefMousePressed && (spawnTimer.getElapsedTime().asMilliseconds() >= rateOfFire || spawnTimer.getElapsedTime().asMilliseconds() == 0))
    {
        _bullets.push_back(std::make_shared<Bullet>(std::make_shared<sf::Vector2f>(player->player->getPosition())));    
        spawnTimer.restart();
    }

    // Movement
    if (keyPressedA && !keyPressedD) 
    {
        std::shared_ptr<sf::Vector2f> acc = std::make_shared <sf::Vector2f>(-800.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else if (keyPressedD && !keyPressedA) 
    {
        std::shared_ptr<sf::Vector2f> acc = std::make_shared <sf::Vector2f>(800.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else
    {
        // Apply deceleration when no keys are pressed
        std::shared_ptr<sf::Vector2f> acc = std::make_shared <sf::Vector2f>(800.0f, 0.0f);
        player->decelerate(acc, deltaTime);
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

        // Movement
        if (event.key.code == sf::Keyboard::D) 
        {
            keyPressedD = true;
        }
        else if (event.key.code == sf::Keyboard::A) 
        {
            keyPressedA = true;
        }
    }
    else if (event.type == event.KeyReleased) 
    {
        if (event.key.code == sf::Keyboard::D) 
        {
            keyPressedD = false;
        }
        else if (event.key.code == sf::Keyboard::A) 
        {
            keyPressedA = false;
        }
    }
}

void Game::update(float deltaTime)
{
    // Update starfield
    stars->updateStars(GameWindow, deltaTime);

    // Update player
    player->updateMovement(deltaTime);

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

    // Draw with bloom
    renderTexture->setActive(true);
    renderTexture->clear(sf::Color::Black);

        // Draw starfield
        stars->draw(GameWindow, renderTexture);

        // Draw bullets (NEEDS FIX)
        for (auto& bulletPtr : _bullets)
        {
            bulletPtr->draw(GameWindow, renderTexture);
        }

        // Apply bloom
        if (bloom)
        {
            shaders->applyBloom(renderTexture);
        }        

    // Draw no bloom
    
        // Draw player
        player->draw(GameWindow, renderTexture);

        // Draw enemies
        for (auto& enemyPtr : _enemies) 
        {
            enemyPtr->draw(GameWindow);
        }

        // Draw fps counter
        fpsCounter.draw(GameWindow);
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
