#include "FPSCounter.h"
#include "Game.h"
#include "Player.h"
sf::RenderWindow* Game::GameWindow;
bool Game::keyPressedA = false;
bool Game::keyPressedD = false;
bool Game::spacePressed = false;
bool Game::bloom = true;
bool playerHidden = false;
float rateOfFire = 150.0f;
bool isIntro = true;

Game::Game(sf::RenderWindow* window, std::shared_ptr<sf::Font> font):
Font(font)
{
    // CONVERSION FACTOR (scale of the game)
    Settings::setConversionFactor(100.0f);

    // Create FPSCounter
    fpsCounter = std::make_shared<FPSCounter>(0.0f, 0.0f, 150.0f, 0.0f, font);

    //Init RenderWindow
    GameWindow = window;

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

    // Create a texture to render on for shader application
    renderTexture1 = std::make_shared<sf::RenderTexture>();
    if (!renderTexture1->create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "GAME: FAILED TO CREATE RENDER TEXTURE";
    }
    
    //REPLACE THIS WITH LEVEL INIT
    // Create EnemyFormation, the class that creates, spawns, moves, draws and despawns enemies

    //LAYOUT
    std::vector<std::vector<int>> formation1 = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, // Row 1
        {3, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3}, // Row 2
        {3, 3, 1 ,3, 1, 3, 2, 2, 2, 3, 1, 3, 1 ,3 ,3}, // Row 3
        {3, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3}, // Row 4
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}  // Row 5
    };    

    // Pointer to the layout
    std::shared_ptr<std::vector<std::vector<int>>> formationPtr = std::make_shared<std::vector<std::vector<int>>>(formation1);   

    // Spawning the formation
    formation = std::make_shared<EnemyFormation>(formationPtr);

    // Spawn player in the center, hide cursor and start the game's main loop
    std::shared_ptr<sf::Vector2f> playerSpawnPos = std::make_shared<sf::Vector2f>(GameWindow->getSize().x / 2, GameWindow->getSize().y + 3.0f * Settings::getConversionFactor());
    player = std::make_shared<Player>(playerSpawnPos);
    GameWindow->setMouseCursorVisible(false);

    // Start the main game loop
	mainLoop();
}

void Game::mainLoop()
{
    while (GameWindow->isOpen())
    {
        // Time it took to calculate the frame
        float deltaTime = clock.restart().asSeconds();
        if (isIntro)
        {
            intro(deltaTime);
        }
        handleInput(deltaTime);
        update(deltaTime);
        draw(deltaTime);
        dispose();
    }
}

void Game::intro(float deltaTime)
{
    float offsetY = GameWindow->getSize().y / 90;
    if(player->getPositionM().y * Settings::getConversionFactor() >= GameWindow->getSize().y -  offsetY)
    {
        sf::Vector2f acc(0.0f, -3.0f);
        player->accelerate(acc, deltaTime);
    }
    else 
    {
        sf::Vector2f acc(0.0f, 10.0f);
        player->decelerate(acc, deltaTime);
    }
}

void Game::mouse(float deltaTime, sf::Event event)
{
    
    if (event.type == event.MouseButtonPressed) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            spacePressed = true;
        }
    }
    if (event.type == event.MouseButtonReleased) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            spacePressed = false;
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
    if (spacePressed && (spawnTimer.getElapsedTime().asMilliseconds() >= rateOfFire || spawnTimer.getElapsedTime().asMilliseconds() == 0))
    {
        projectiles.push_back(player->shoot((player->getPositionM())));    
        spawnTimer.restart();
    }

    // Movement
    if (keyPressedA && !keyPressedD) 
    {
        sf::Vector2f acc(-9.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else if (keyPressedD && !keyPressedA) 
    {
        sf::Vector2f acc(9.0f, 0.0f);
        player->accelerate(acc, deltaTime);
    }
    else
    {
        // Apply deceleration when no keys are pressed
        sf::Vector2f dec(10.0f, 0.0f);
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
            //delete GameWindow;            
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

        // Shoot
        if (event.key.code == sf::Keyboard::Space)
        {
            spacePressed = true;
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
        else if (event.key.code == sf::Keyboard::Space)
        {
            spacePressed = false;
        }
    }
}

void Game::update(float deltaTime)
{
    // Update starfield
    stars->updateStars(GameWindow, deltaTime);

    // Update enemies (passing a pointer to _projectiles to add EnemyBullets
    formation->updateFormation(deltaTime, &projectiles);

    // Update player
    player->updateMovement(deltaTime);

    // Update projectiles, check if they hit someone
    for (auto& projectilePtr : projectiles) 
    {
        projectilePtr->updatePosition(deltaTime);
        formation->checkProjectileCollision(projectilePtr);
        if (projectilePtr->getTeam() == 1) 
        {
            if (player->isHit(projectilePtr))
            {
                projectilePtr->kill();
                player->applyDamage(projectilePtr->getDamage());
                ParticleEffects::createSparks(projectilePtr->getPositionM(), 5.0f);
            }
        }
    }

    // Update particles
    ParticleEffects::update(deltaTime);
    formation->checkParticleCollision(deltaTime);

    // Update FPS counter
    fpsCounter->displayFps(deltaTime);
}

void Game::draw(float deltaTime)
{
    GameWindow->clear(sf::Color::Black);

    renderTexture->setActive(true);
    renderTexture1->setActive(true);

    // Draw starfield
    stars->draw(GameWindow, renderTexture1);
   
   

    // Draw bullets
    for (auto& bulletPtr : projectiles)
    {
        bulletPtr->draw(GameWindow, renderTexture1);
    }

    // Draw enemies
    formation->draw(GameWindow, renderTexture1);

    // Draw particles
    ParticleEffects::draw(GameWindow, renderTexture1);

    // Draw player
    player->draw(GameWindow, renderTexture1);

    // Draw fps counter
    fpsCounter->draw(GameWindow);

    // Apply bloom
    if (bloom)
    {
        //shaders->applyBloom(renderTexture, GameWindow);
        shaders->applyBloom(renderTexture1, GameWindow);
        //shaders->applyAddition(renderTexture, renderTexture1, GameWindow);
    }
    // Reset
    renderTexture->setActive(false);
    renderTexture1->setActive(false);
    renderTexture->clear(sf::Color::Black);
    renderTexture1->clear(sf::Color::Black);

    //Display
    GameWindow->display();
}

void Game::dispose()
{
    // Dispose projectiles
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

    // Dispose dead enemies
    formation->despawnDead();

    // Dispose particles
    ParticleEffects::dispose();

    // Despawn dead player (only hiding the sprite)
    if (player->isDead() && !playerHidden) 
    {
        ParticleEffects::createExplosion(player->getPositionM(), 5.0f);
        player->hide();
        playerHidden = true;
    }
}
