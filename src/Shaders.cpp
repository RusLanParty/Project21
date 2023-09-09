#include "Shaders.h"
#include <iostream>
sf::Shader Shaders::bloomX;
sf::Shader Shaders::bloomY;
sf::Shader Shaders::add;

void Shaders::loadShaders()
{
    if (!bloomX.loadFromFile("Shaders/BloomX.frag", sf::Shader::Fragment))
    {
        std::cout << "SHADERS: Failed to load BloomX.frag" << "\n";
    }
    else
    {
        std::cout << "SHADERS: BloomX.frag - SUCCESS" << "\n";
    }
    if (!bloomY.loadFromFile("Shaders/BloomY.frag", sf::Shader::Fragment))
    {
        std::cout << "SHADERS: Failed to load BloomY.frag" << "\n";
    }
    else
    {
        std::cout << "SHADERS: BloomY.frag - SUCCESS" << "\n";
    }
    if (!add.loadFromFile("Shaders/add.frag", sf::Shader::Fragment))
    {
        std::cout << "SHADERS: Failed to load add.frag" << "\n";
    }
    else
    {
        std::cout << "SHADERS: add.frag - SUCCESS" << "\n";
    }

    // Set uniforms
    float sigma = 3.0f;
    float glowMultiplier = 1.5f;
    float width = Game::GameWindow->getSize().x;
    float height = Game::GameWindow->getSize().y;

    bloomX.setUniform("sigma", sigma);
    bloomX.setUniform("glowMultiplier", glowMultiplier);
    bloomX.setUniform("width", width);

    bloomY.setUniform("sigma", sigma);
    bloomY.setUniform("glowMultiplier", glowMultiplier);
    bloomY.setUniform("height", height);
}

void Shaders::applyBloom(std::shared_ptr<sf::RenderTexture> xRenderTexture, sf::RenderWindow* GameWindow)
{ 
    // Create temp textures
    sf::RenderTexture tempTexture;
    sf::RenderTexture yRenderTexture;
    sf::Sprite sprite(xRenderTexture->getTexture());
    sf::Texture sourceTexture(xRenderTexture->getTexture());
    if (!tempTexture.create(GameWindow->getSize().x, GameWindow->getSize().y)) 
    {
        std::cout << "SHADERS: failed to create tempTexture" << "\n";
    }
    if (!yRenderTexture.create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
       std::cout << "SHADERS: failed to create yRenderTexture" << "\n";
    }
    
    bloomX.setUniform("sourceTexture", sourceTexture);
    bloomY.setUniform("sourceTexture", sourceTexture);
    
    // X bloom
    xRenderTexture->draw(sprite, &bloomX);
    xRenderTexture->display();
    // Y bloom
    yRenderTexture.draw(sprite, &bloomY);
    yRenderTexture.display();
   
    // Add X + Y
    add.setUniform("source", xRenderTexture->getTexture());
    add.setUniform("bloom", yRenderTexture.getTexture());    
    tempTexture.draw(sprite, &add);

    // Draw final result to window
    sprite.setTexture(tempTexture.getTexture());
    GameWindow->draw(sprite);
    xRenderTexture->clear(sf::Color::Transparent);
}

void Shaders::applyAddition(std::shared_ptr<sf::RenderTexture> xRenderTexture, std::shared_ptr<sf::RenderTexture> xRenderTexture1, sf::RenderWindow* GameWindow)
{
    // Create temp textures
    sf::RenderTexture tempTexture;
    sf::Sprite sprite(xRenderTexture->getTexture());
    if (!tempTexture.create(GameWindow->getSize().x, GameWindow->getSize().y))
    {
        std::cout << "SHADERS: failed to create tempTexture" << "\n";
    }

    // Add to original frame
    add.setUniform("bloom", xRenderTexture1->getTexture());
    add.setUniform("source", xRenderTexture->getTexture());
    tempTexture.draw(sprite, &add);
    //tempTexture.display();
    
    // Draw final result to window
    sprite.setTexture(tempTexture.getTexture());
    GameWindow->draw(sprite);
    xRenderTexture->clear(sf::Color::Transparent);
}
