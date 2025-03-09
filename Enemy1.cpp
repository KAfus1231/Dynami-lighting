#include "Enemy1.h"
#include <cstdlib>
#include <stdlib.h> 

Enemy1::Enemy1()
{
	initialize();
}

Enemy1::~Enemy1()
{
}

void Enemy1::initialize()
{
	speed = 0.7f;
	widht = 32.0f;
	height = 32.0f;
	hitboxColor = sf::Color::Red;

	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(200, 150);

	timeForMovement = 0.5f;
}


void Enemy1::move(Player& player)
{
	isMovingUp = false;
	isMovingLeft = false;
	isMovingDown = false;
	isMovingRight = false;

	if (clockForMovement.getElapsedTime().asSeconds() > timeForMovement)
	{
		randNumForMovement = std::rand() % 4 + 1;
		clockForMovement.restart();
	}

	if (inView)
	{
		sf::Vector2f direction = player.getHitboxPosition() - hitbox.getPosition();
	}


	switch (randNumForMovement)
	{
	case 1: hitbox.move(0, -3 * speed), isMovingUp = true; break;
	case 2: hitbox.move(-3 * speed, 0), isMovingLeft = true; break;
	case 3: hitbox.move(0, 3 * speed), isMovingDown = true; break;
	case 4: hitbox.move(3 * speed, 0), isMovingRight = true; break;

	default:
		break;
	}

	/*std::system("cls");*/
	/*std::cout << isMoovingUp << " " << isMoovingLeft << " " << isMoovinDown << " " << isMoovingRight << std::endl;*/
}

void Enemy1::update(Player& player)
{
	move(player);
	fieldOfView(player);
}

bool Enemy1::fieldOfView(Player& player)
{
	
	if (inView)
	{
		view.setSize(sf::Vector2f(192, 192));
		view.setPosition(hitbox.getPosition().x - 80, hitbox.getPosition().y - 80);
		view.setFillColor(sf::Color::Transparent);
		view.setOutlineColor(sf::Color::Red);
		view.setOutlineThickness(2);
	}
	
	else
	{
		view.setSize(sf::Vector2f(128, 128));
		view.setPosition(hitbox.getPosition().x - 48, hitbox.getPosition().y - 48);
		view.setFillColor(sf::Color::Transparent);
		view.setOutlineColor(sf::Color::Blue);
		view.setOutlineThickness(2);
	}

	if (view.getGlobalBounds().intersects(player.getHitbox().getGlobalBounds()))
	{
		inView = true;
		ClockForView.restart();
	}

	if (ClockForView.getElapsedTime().asSeconds() > 4)
	{
		inView = false;
	}

	return inView;
}

void Enemy1::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
	window.draw(view);
}