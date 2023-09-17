#include "Game.h"
sf::RenderWindow* Game::GameWindow;
bool keyPressedA = false;
bool keyPressedD = false;
bool primaryPressed = false;
bool secondaryPressed = false;
bool Game::bloom = true;
bool playerHidden = false;
float primaryRateOfFire = 150.0f;
float secondaryRateOfFire = 1500.0f;
bool Game::isIntro = false;
sf::RenderTexture* Game::renderTexture = new sf::RenderTexture();
sf::RenderTexture* Game::renderTexture1 = new sf::RenderTexture();
sf::Font* Game::Font = new sf::Font;

Game::Game(sf::RenderWindow* window)
{
    // CONVERSION FACTOR (scale of the game)
    Settings::setConversionFactor(100.0f);

    // Load font
    if (!Font->loadFromFile("Fonts/arial.ttf"))
    {
        std::cout << "Error loading font" << "\n";
    }

    // Create FPSCounter
    FPSCounter::init(0.0f, 0.0f, 100.0f, 0.0f, Font);

    //Init RenderWindow
    GameWindow = window;

    // Init shaders
    Shaders::loadShaders();
    
    // Create a starfield
    Starfield::createStarfield(GameWindow);

    // Create a texture to render on for shader application
    if (!renderTexture->create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "GAME: FAILED TO CREATE RENDER TEXTURE";
    }    
    if (!renderTexture1->create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "GAME: FAILED TO CREATE RENDER TEXTURE";
    }
    
    // Init menu
    Menu::initMenu();

    //REPLACE THIS WITH LEVEL INIT
    // Create EnemyFormation, the class that creates, spawns, moves, draws and despawns enemies

    //LAYOUT
    std::vector<std::vector<int>> formation1 = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, // Row 1
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3}, // Row 2
        {3, 2, 1 ,1, 1, 1, 1, 3, 3, 3, 3, 3, 1 ,1 ,1, 1, 1, 2, 3}, // Row 3
        {3, 2, 1, 2, 2, 2, 2, 3, 0, 0, 0, 3, 2, 2, 2, 2, 1, 2, 3}, // Row 4
        {3, 2, 1, 2, 2, 2, 2, 3, 0, 0, 0, 3, 2, 2, 2, 2, 1, 2, 3}, // Row 5
        {3, 2, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 2, 2, 2, 2, 1, 2, 3}, // Row 6
        {3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3}, // Row 7
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3}, // Row 8
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}  // Row 9
    };    

    // Pointer to the layout
    std::shared_ptr<std::vector<std::vector<int>>> formationPtr = std::make_shared<std::vector<std::vector<int>>>(formation1);   

    // Spawning the formation
    formation = std::make_shared<EnemyFormation>(formationPtr);

    // Hide cursor
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

        // Menu
        if (Menu::isActive())
        {     
            Menu::menuLoop(deltaTime);
        }
        
        // Game loop
        else 
        {                        
            if (Game::isIntro)
            {
                intro(deltaTime);
            }
            handleInput(deltaTime);
            update(deltaTime);
            draw(deltaTime);
            dispose();
        }
    }
}

void Game::intro(float deltaTime)
{    
    float offsetY = GameWindow->getSize().y / 10;
    if(Player::getPositionM().y * Settings::getConversionFactor() >= GameWindow->getSize().y -  offsetY)
    {
        sf::Vector2f acc(0.0f, -0.5f);
        Player::accelerate(acc, deltaTime);
    }

    else 
    {
        sf::Vector2f dec(0.0f, 2.0f);
        Player::decelerate(dec, deltaTime);
        if (Player::getVelocity().y >= 0.0f)
        {            
            isIntro = false;            
        }
    }
}

void Game::mouse(float deltaTime, sf::Event event)
{
    
    if (event.type == event.MouseButtonPressed) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            primaryPressed = true;
        }
        else if (event.key.code == sf::Mouse::Right)
        {
            secondaryPressed = true;
        }
    }
    if (event.type == event.MouseButtonReleased) 
    {
        if (event.key.code == sf::Mouse::Left) 
        {
            primaryPressed = false;
        }
        else if (event.key.code == sf::Mouse::Right)
        {
            secondaryPressed = false;
        }
    }
}

void Game::handleInput(float deltaTime)
{
    // Check for events
    sf::Event event;
    while (GameWindow->pollEvent(event))
    {
        if (!Game::isIntro) 
        {
            keyboard(deltaTime, event);
            mouse(deltaTime, event);
        }
    }

    // Respond to events
    
    // Shooting primary
    if (primaryPressed && !secondaryPressed && (primaryFireTimer.getElapsedTime().asMilliseconds() >= primaryRateOfFire || primaryFireTimer.getElapsedTime().asMilliseconds() == 0))
    {
        projectiles.push_back(Player::shootPrimary((Player::getPositionM())));
        primaryFireTimer.restart();
    }

    // Shooting secondary
    if (secondaryPressed && !primaryPressed && (secondaryFireTimer.getElapsedTime().asMilliseconds() >= secondaryRateOfFire || secondaryFireTimer.getElapsedTime().asMilliseconds() == 0))
    {
        projectiles.push_back(Player::shootSecondary((Player::getPositionM())));
        secondaryFireTimer.restart();
    }

    // Movement
    if (keyPressedA && !keyPressedD) 
    {
        sf::Vector2f acc(-9.0f, 0.0f);
        Player::accelerate(acc, deltaTime);
    }
    else if (keyPressedD && !keyPressedA) 
    {
        sf::Vector2f acc(9.0f, 0.0f);
        Player::accelerate(acc, deltaTime);
    }
    else
    {
        // Apply deceleration when no keys are pressed
        sf::Vector2f dec(10.0f, 0.0f);
        Player::decelerate(dec, deltaTime);
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
            primaryPressed = true;
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
            primaryPressed = false;
        }
    }
}

void Game::update(float deltaTime)
{
    // Update starfield
    Starfield::updateStars(GameWindow, deltaTime);

    // Update enemies (passing a pointer to _projectiles to add EnemyBullets
    formation->updateFormation(deltaTime, &projectiles);

    // Update player
    Player::updateMovement(deltaTime);

    // Update projectiles, check if they hit someone
    for (auto& projectilePtr : projectiles) 
    {
        projectilePtr->updatePosition(deltaTime);
        formation->checkProjectileCollision(projectilePtr);
        if (projectilePtr->getTeam() == 1) 
        {
            if (Player::isHit(projectilePtr))
            {
                projectilePtr->kill();
                Player::applyDamage(projectilePtr->getDamage());
                ParticleEffects::createSparks(projectilePtr->getPositionM(), 5.0f);
            }
        }
    }

    // Update particles
    ParticleEffects::update(deltaTime);
    formation->checkParticleCollision(deltaTime);

    // Update FPS counter
    FPSCounter::update(deltaTime);
    FPSCounter::displayOjbectCount(Starfield::getCurrentStarsCount());
}

void Game::draw(float deltaTime)
{
    GameWindow->clear(sf::Color::Black);

    renderTexture->setActive(true);
    renderTexture1->setActive(true);

    // Draw starfield
    Starfield::draw(GameWindow, renderTexture1);

    // Draw bullets
    for (auto& bulletPtr : projectiles)
    {
        bulletPtr->draw(GameWindow, renderTexture1);
    }


    // Draw particles
    ParticleEffects::draw(GameWindow, renderTexture1);

   

    // Apply bloom
    if (bloom)
    {
        //Shaders::applyBloom(renderTexture, GameWindow);
        Shaders::applyBloom(renderTexture1, GameWindow);
        //Shaders::applyAddition(renderTexture, renderTexture1, GameWindow);
    }

    // Draw enemies
    formation->draw(GameWindow, renderTexture1);

    // Draw player
    Player::draw(GameWindow, renderTexture1);

    // Reset
    renderTexture->clear(sf::Color::Black);
    renderTexture1->clear(sf::Color::Black);
    renderTexture->setActive(false);
    renderTexture1->setActive(false);

    // Draw fps counter
    FPSCounter::draw(GameWindow);

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
    if (Player::isDead() && !playerHidden)
    {
        ParticleEffects::createExplosion(Player::getPositionM(), 5.0f);
        Player::hide();
        playerHidden = true;
    }
}
