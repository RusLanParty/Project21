#include "EnemyFormation.h"
#include "ParticleEffects.h"
#include "Game.h"

EnemyFormation::EnemyFormation(std::shared_ptr<std::vector<std::vector<int>>> formationLayout) :
    _spawnT(0.0f),
    _spawnThresh(0.05f)
{
    const auto& layout = *formationLayout;

    // Calculate the total width of the formation based on columns, enemy width, and spacing
    float totalFormationWidth = layout[0].size() * (50.0f + 50.0f) - 50.0f;

    // Calculate the horizontal offset to center the formation
    float offsetX = (Game::GameWindow->getSize().x - totalFormationWidth) / 2.0f;

    // Offset from the top
    sf::Vector2f offset(offsetX, 50.0f);

    for (size_t row = 0; row < layout.size(); ++row)
    {
        for (size_t col = 0; col < layout[row].size(); ++col)
        {
            sf::Vector2f enemyPosition = offset + sf::Vector2f(col * (50.0 + 50.0), row * 50.0);
            _spawnQue.emplace(std::make_shared<Enemy>(enemyPosition, layout[row][col]));
        }
    }
}
void EnemyFormation::checkProjectileCollision(std::shared_ptr<Projectile> proj)
{
    if (!_enemies.empty()) 
    {
        if (proj->getTeam() == 0) 
        {
            for (auto& enemyPtr : _enemies)
            {
                if (enemyPtr->isHit(proj))
                {
                    proj->kill();
                    enemyPtr->applyDamage(proj->getDamage());
                    enemyPtr->flash();

                    // Get color of enemie for the particles
                    float hue = enemyPtr->getColor().r;
                    float sat = enemyPtr->getColor().g;
                    float val = enemyPtr->getColor().b;
                    ParticleEffects::createSparks(proj->getPositionM(), 5.0f, hue, sat, val);
                }
            }
        }
    }
}

void EnemyFormation::checkParticleCollision(float deltaTime)
{
    std::vector<std::shared_ptr<Particle>> particles = *ParticleEffects::getAllParticles();
    if (!_enemies.empty())
    {
        if (!particles.empty()) 
        {
            for (auto& enemyPtr : _enemies)
            {
                for (auto& particle : particles) 
                {
                    if (enemyPtr->isHit(particle))
                    {
                        particle->kill();
                        enemyPtr->applyDamage(particle->getDamage(deltaTime));

                        // ININITE RECURSION
                        //ParticleEffects::createSparks(particle->getPositionM(), 5.0f);
                    }
                }
            }
       }
    }
}

void EnemyFormation::updateFormation(float deltaTime, std::vector<std::shared_ptr<Projectile>>* projectiles)
{
    // Spawn formation
    if (!_spawnQue.empty()) 
    {
        _spawnT += deltaTime;

        if (_spawnT > _spawnThresh) 
        {
            std::shared_ptr<Enemy> enemy = _spawnQue.front();
            _spawnQue.pop();
            enemy->flash();
            _enemies.push_back(enemy);
            _spawnT = 0.0f;

            // Set velocity
            if (_spawnQue.empty())
            {                
                sf::Vector2f vel(1.0f, 0.0f);
                for (auto& enemy : _enemies) 
                {
                    enemy->setVelocity(vel);
                }
            }
        }
    }

    bool reverse = false;
    if (!_enemies.empty()) 
    {
        for (auto& enemyPtr : _enemies)
        {
            // Update movement and shoot
            enemyPtr->updateMovement(deltaTime);
            if (enemyPtr->canShoot()) 
            {
                enemyPtr->flash();
                projectiles->push_back(enemyPtr->shoot(enemyPtr->getPositionM()));
            }

            // Check bounds
            if (enemyPtr->touchedBounds()) 
            {
                enemyPtr->flash();
                reverse = true;
            }

            enemyPtr->updateColor(deltaTime);
        }

        // Change formation's direction if reached bounds
        if (reverse) 
        {
            for (auto& enemyPtr : _enemies)
            {   
                enemyPtr->invertXVelocity();
                reverse = false;
            }
            this->moveDown();
        }
    }
}

void EnemyFormation::moveDown()
{
    for (auto& enemyPtr : _enemies) 
    {
        sf::Vector2f newPos(enemyPtr->getPositionM().x, enemyPtr->getPositionM().y + 0.1f);
        enemyPtr->setPositionM(newPos);
    }
}

void EnemyFormation::draw(sf::RenderWindow* GameWindow, std::shared_ptr<sf::RenderTexture> renderTexture)
{
    if (!_enemies.empty()) 
    {
        if (Game::bloom) 
        {
            for (auto& enemyPtr : _enemies) 
            {
                enemyPtr->draw(renderTexture);
            }
        }
        else 
        {
            for (auto& enemyPtr : _enemies)
            {
                enemyPtr->draw(GameWindow);
            }
        }
    }
}

void EnemyFormation::despawnDead()
{
    auto it1 = _enemies.begin();
    while (it1 != _enemies.end())
    {
        if ((*it1)->isDead())
        {
            ParticleEffects::createExplosion((*it1)->getPositionM(), 5.0f);
            (*it1).reset();

            it1 = _enemies.erase(it1);
        }
        else
        {            
            ++it1;
        }
    }
}

