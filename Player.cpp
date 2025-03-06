#include "Player.h"

Player::Player()
{
	initialize();
}

Player::~Player()
{
}

void Player::initialize()
{
	speed = 1.0f;
	widht = 32.0f;
	height = 32.0f;
	hitboxColor = sf::Color::Green;

	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(400, 300);
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isMoovinDown)
	{
		hitbox.move(0, -3 * speed);
		isMoovingUp = true;
	}
	else
		isMoovingUp = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isMoovingRight)
	{
		hitbox.move(-3 * speed, 0);
		isMoovingLeft = true;
	}
	else
		isMoovingLeft = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isMoovingUp)
	{
		hitbox.move(0, 3 * speed);
		isMoovinDown = true;
	}
	else
		isMoovinDown = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isMoovingLeft)
	{
		hitbox.move(3 * speed, 0);
		isMoovingRight = true;
	}
	else
		isMoovingRight = false;

}

void Player::update()
{
	move();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
}