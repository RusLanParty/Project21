#include "FPSCounter.h"
#include "Game.h"
#include "Player.h"
bool Game::keyPressedA = false;
bool Game::keyPressedD = false;
bool Game::lefMousePressed = false;
bool Game::bloom = true;
sf::RenderWindow* Game::GameWindow;
float rateOfFire = 100.0f;

Game::Game(sf::RenderWindow* window, std::shared_ptr<sf::Font> font):
Font(font)
{
    // Create FPSCounter
    fpsCounter = std::make_shared<FPSCounter>(0.0f, 0.0f, 150.0f, 0.0f, font);

    //Init RenderWindow
    GameWindow = window;

    // CONVERSION FACTOR (scale of the game)
    Settings::setConversionFactor(200.0f);

    // Spawn player in the center, hide cursor and start the game's main loop
    std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(GameWindow->getSize().x / 2 , GameWindow->getSize().y - 1.0f * Settings::getConversionFactor());
    player = std::make_shared<Player>(playerSpawnPos);
    GameWindow->setMouseCursorVisible(false);

    // Init shaders
    shaders = std::make_shared<Shaders>(GameWindow);

    // Create starfield
    stars = std::make_shared<Starfield>(GameWindow);
    
    // Create a texture to render on for shader application
    renderTexture = std::make_shared<sf::RenderTexture>();
    if (!renderTexture->create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "GAME: FAILED TO CREATE RENDER TEXTURE";
    }

    // Create EnemyFormation, the class that creates, spawns, moves, draws and despawns enemies
    formation = std::make_shared<EnemyFormation>();

    // Start the main game loop
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
        projectiles.push_back(std::make_shared<Bullet>(std::make_shared<sf::Vector2f>(player->getPositionM())));    
        spawnTimer.restart();
    }

    // Movement
    if (keyPressedA && !keyPressedD) 
    {
        std::shared_ptr<sf::Vector2f> acc = std::make_shared <sf::Vector2f>(-5.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else if (keyPressedD && !keyPressedA) 
    {
        std::shared_ptr<sf::Vector2f> acc = std::make_shared <sf::Vector2f>(5.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else
    {
        // Apply deceleration when no keys are pressed
        std::shared_ptr<sf::Vector2f> dec = std::make_shared <sf::Vector2f>(20.0f, 0.0f);
        player->decelerate(dec, deltaTime);
    }
}

void Game::keyboard(float deltaTime, sf::Event event)
{
    if (event.type == event.KeyPressed) 
    {
        // Exit
        if (event.key.code == sf::Keyboard::Escape) 
        {            
            GameWindow->close();
            delete GameWindow;            
        }
        // Toggle bloom shader
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

    // Update projectiles, check if they hit someone
    for (auto& projectilePtr : projectiles) 
    {
        projectilePtr->updatePosition(deltaTime);
        formation->checkProjectileCollision(projectilePtr);
    }

    // Update enemies
    formation->updateFormation(deltaTime);

    // Update FPS counter
    fpsCounter->displayFps(deltaTime);
}

void Game::draw(float deltaTime)
{
    GameWindow->clear(sf::Color::Black);

    // Draw with bloom
    renderTexture->setActive(true);
    renderTexture->clear(sf::Color::Black);

        // Draw starfield
        stars->draw(GameWindow, renderTexture);

        // Draw bullets
        for (auto& bulletPtr : projectiles)
        {
            bulletPtr->draw(GameWindow, renderTexture);
        }

        // Apply bloom
        if (bloom)
        {
            shaders->applyBloom(renderTexture, GameWindow);
        }        

    // Draw no bloom
    
        // Draw player
        player->draw(GameWindow, renderTexture);

        // Draw enemies
        formation->draw(GameWindow);

        // Draw fps counter
        fpsCounter->draw(GameWindow);
    GameWindow->display();
}

void Game::dispose()
{
    // Despawn bullets
    auto it = projectiles.begin();
    while (it != projectiles.end())
    {
        if ((*it)->isDead())
        {
            (*it).reset();            

            // Remove the element from the vector and advance the iterator
            it = projectiles.erase(it);
        }
        else
        {
            // Move to the next element
            ++it;
        }
    }

    // Despawn dead enemies
    formation->despawnDead();
}
