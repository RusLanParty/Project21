#include "Player.h"

static float maxAcc = 20.0f;
static float maxSpeed = 10.0f;
static float _health = 300.0f;

sf::Vector2f Player::velocity;
sf::Vector2f Player::acceleration;
sf::Texture Player::playerTexture;
sf::Sprite Player::player;

void Player::load(std::shared_ptr<sf::Vector2f> spawnPos)
{		
	
	// Velocity & acceleration vectors
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	acceleration.x = 0.0f;
	acceleration.y = 0.0f;

	// Load player texture
	if (!playerTexture.loadFromFile("Assets/player.png"))
	{
		std::cout << "PLAYER: ERROR LOADING PLAYER.PNG" << "\n";
	}
	else 
	{
		std::cout << "PLAYER: PLAYER.PNG - SUCCESS" << "\n";
	}
	player.setTexture(playerTexture);
	player.setRotation(270.0f);
	player.setScale(0.3f, 0.3f);
	player.setOrigin(player.getLocalBounds().getSize().x / 2, player.getLocalBounds().getSize().y / 2);
	player.setPosition(*spawnPos);	

	// Darken texture
	sf::Color darkColor(45.0f, 45.0f, 45.0f);
	player.setColor(darkColor);
}

void Player::updateMovement(float deltaTime)
{	
	// Conversion pixels/meters
	float conv = Settings::getConversionFactor();

	// Set new position
	sf::Vector2f newPos(getPositionM() + velocity * deltaTime);
	setPositionM(newPos);

	// Check bounds
	if (getPositionM().x > Game::GameWindow->getSize().x / conv  - player.getLocalBounds().width * 0.1f / conv)
	{
		sf::Vector2f pos(Game::GameWindow->getSize().x / conv - player.getLocalBounds().width * 0.1f / conv, player.getPosition().y / conv);
		setPositionM(pos);
		velocity.x = 0.0f;
	}
	else if (getPositionM().x < player.getLocalBounds().width * 0.1f / conv)
	{
		sf::Vector2f pos(player.getLocalBounds().width * 0.1f / conv, player.getPosition().y / conv);
		setPositionM(pos);
		velocity.x = 0.0f;
		acceleration.x = 0.0f;
	}	

	// Reset acceleration
	acceleration.x = 0.0f;

	// Create thrust particles
	sf::Vector2f engine1(getPositionM().x - 0.35f, getPositionM().y + 1.1f);
	sf::Vector2f engine2(getPositionM().x + 0.25f, getPositionM().y + 1.1f);
	ParticleEffects::createThrust(engine1, 5.0f);
	ParticleEffects::createThrust(engine2, 5.0f);
}

bool Player::isHit(std::shared_ptr<Projectile> proj)
{
	return player.getGlobalBounds().intersects(proj->getGlobalBounds());
}

bool Player::isDead()
{
	return _health <= 0.0f;
}

void Player::applyDamage(float damage)
{
	_health -= damage;
}

std::shared_ptr<Bullet> Player::shootPrimary(sf::Vector2f pos)
{
	std::shared_ptr<Bullet> bul = std::make_shared<Bullet>(pos);
	return bul;	
}

std::shared_ptr<Rocket> Player::shootSecondary(sf::Vector2f pos)
{
	std::shared_ptr<Rocket> rocket = std::make_shared<Rocket>(pos);
	return rocket;
}

void Player::hide()
{
	player.setColor(sf::Color::Transparent);
}

void Player::draw(sf::RenderWindow* GameWindow, sf::RenderTexture* renderTexture)
{
	if (Game::bloom)
	{		
		renderTexture->draw(player);
		renderTexture->display();
	}
	else
	{
		GameWindow->draw(player);
	}
}

void Player::accelerate(sf::Vector2f& acc, float deltaTime)
{		
	// Update acceleration
	acceleration += acc;
	if (acceleration.x > maxAcc)
	{
		acceleration.x = maxAcc;
	}
	else if (acceleration.x < -maxAcc)
	{
		acceleration.x = -maxAcc;
	}

	// Update velocity
	velocity += acceleration * deltaTime;
	if (velocity.x > maxSpeed)
	{
		velocity.x = maxSpeed;
	}
	else if (velocity.x < -maxSpeed)
	{
		velocity.x = -maxSpeed;
	}
}

void Player::decelerate(sf::Vector2f& dec, float deltaTime)
{	
	acceleration.x = 0.0f;
	acceleration.y = 0.0f;

	// X deceleration
	if (velocity.x > 0.0f)
	{
		velocity.x -= dec.x * deltaTime;		

		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	else if (velocity.x < 0.0f)
	{
		velocity.x += dec.x * deltaTime;
		if (velocity.x > 0.0f)
		{
			velocity.x = 0.0f;
		}
	}

	// Y deceleration
	if (velocity.y > 0.0f)
	{
		velocity.y -= dec.y * deltaTime;

		if (velocity.y < 0.0f)
		{
			velocity.y = 0.0f;
		}
	}
	else if (velocity.y < 0.0f)
	{
		velocity.y += dec.y * deltaTime;
		if (velocity.y > 0.0f)
		{
			velocity.y = 0.0f;
		}
	}
}

sf::Vector2f Player::getVelocity()
{
	return velocity;
}

sf::Vector2f Player::getPositionM()
{
	return player.getPosition() / Settings::getConversionFactor();
}

void Player::setPositionM(sf::Vector2f& pos)
{
	player.setPosition(pos * Settings::getConversionFactor());
}
