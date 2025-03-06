#include "Enemy1.h"
#include <cstdlib>

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


void Enemy1::move()
{
	
	if (clockForMovement.getElapsedTime().asSeconds() > timeForMovement)
	{
		randNumForMovement = std::rand() % 4 + 1;
		std::cout << randNumForMovement << std::endl;
		clockForMovement.restart();
	}

	randNumForMovement == 1 ? hitbox.move(0, -3 * speed) : (randNumForMovement == 2 ? hitbox.move(0, 3 * speed) :
		(randNumForMovement == 3 ? hitbox.move(-3 * speed, 0) : hitbox.move(3 * speed, 0)));
}

void Enemy1::update(Player& player)
{
	move();
	fieldOfView(player);
}

bool Enemy1::fieldOfView(Player& player)
{
	view.setSize(sf::Vector2f(128, 128));
	view.setPosition(hitbox.getPosition().x - 48, hitbox.getPosition().y - 48);
	
	if (inView)
	{
		view.setFillColor(sf::Color::Transparent);
		view.setOutlineColor(sf::Color::Red);
		view.setOutlineThickness(2);
	}
	
	else
	{
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