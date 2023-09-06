#include "EnemyFormation.h"

EnemyFormation::EnemyFormation()
{
    sf::Vector2f pos(200.0f, -10.0f);
    sf::Vector2f pos1(400.0f, -10.0f);
    sf::Vector2f pos2(600.0f, -10.0f);
    _enemies.emplace_back(std::make_shared<Enemy>(pos));
    _enemies.emplace_back(std::make_shared<Enemy>(pos1));
    _enemies.emplace_back(std::make_shared<Enemy>(pos2));
}

void EnemyFormation::checkProjectileCollision(std::shared_ptr<Projectile> proj)
{
    if (!_enemies.empty()) 
    {
        for (auto& enemyPtr : _enemies)
        {
            if (enemyPtr->isHit(proj))
            {
                proj->kill();
                enemyPtr->applyDamage(proj->getDamage());
            }
        }
    }
}

void EnemyFormation::updateFormation(float deltaTime)
{
    if (!_enemies.empty()) 
    {
        for (auto& enemyPtr : _enemies)
        {
            enemyPtr->updateMovement(deltaTime);
        }
    }
}

void EnemyFormation::draw(sf::RenderWindow* GameWindow)
{
    if (!_enemies.empty()) 
    {
        for (auto& enemyPtr : _enemies)
        {
            enemyPtr->draw(GameWindow);
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
            (*it1).reset();

            // Remove the element from the vector and advance the iterator
            it1 = _enemies.erase(it1);
        }
        else
        {
            // Move to the next element
            ++it1;
        }
    }
}

