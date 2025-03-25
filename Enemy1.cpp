#include "Enemy1.h"
#include <cstdlib>
#include <stdlib.h> 

Enemy1::Enemy1(Map& map)
{
	initialize();
	hitbox.setPosition(map.getEnemyStartPosition());
}

Enemy1::~Enemy1()
{
}

void Enemy1::initialize()
{
	speed = 0.7f;
	widht = 32.0f;
	height = 32.0f;
	hitboxColor = sf::Color(81, 97, 159);

	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(200, 150);

	collisionChecker.setSize(sf::Vector2f(64, 64));
	collisionChecker.setFillColor(sf::Color::Transparent);
	collisionChecker.setOutlineColor(sf::Color::Yellow);
	collisionChecker.setOutlineThickness(2);

	timeForMovement = 3.0f;

	patrolPoints =
	{
		sf::Vector2f(224, 160),
		sf::Vector2f(320, 160),
		sf::Vector2f(320, 32)
	};
	patrolPointIndex = 0;
	endOfPatrol = false;
}


void Enemy1::move(Player& player)
{
	movePatrol();
}

void Enemy1::movePatrol()
{
	if (patrolPoints.empty())
		return;

	sf::Vector2f target = patrolPoints[patrolPointIndex];

	sf::Vector2f currentPos = hitbox.getPosition();

	// Определяем разницу по осям
	float diffX = target.x - currentPos.x;
	float diffY = target.y - currentPos.y;

	const float threshold = 2.0f;

	isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;

	if (std::abs(diffX) > std::abs(diffY))
	{
		// Движемся по оси X
		if (diffX > threshold) {
			isMovingRight = true;
			hitbox.move(3 * speed, 0);
		}
		else if (diffX < -threshold) {
			isMovingLeft = true;
			hitbox.move(-3 * speed, 0);
		}
	}
	else
	{
		// Движемся по оси Y
		if (diffY > threshold) {
			isMovingDown = true;
			hitbox.move(0, 3 * speed);
		}
		else if (diffY < -threshold) {
			isMovingUp = true;
			hitbox.move(0, -3 * speed);
		}
	}

	sf::Vector2f newPos = hitbox.getPosition();
	if (std::abs(newPos.x - target.x) < threshold && std::abs(newPos.y - target.y) < threshold)
	{
		if (!endOfPatrol)
		{
			patrolPointIndex == patrolPoints.size() - 1 ? endOfPatrol = true : patrolPointIndex++;
		}
		else
		{
			patrolPointIndex == 0 ? endOfPatrol = false : patrolPointIndex--;
		}
	}
}


void Enemy1::moveHarassment(Player& player)
{
	/*if (clockForMovement.getElapsedTime().asSeconds() > timeForMovement)
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
	case 1:
		if (!upCollision)
		{
			hitbox.move(0, -3 * speed);
			isMovingUp = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 1)
				randNumForMovement = 3; break;
		}

	case 2:
		if (!leftCollision)
		{
			hitbox.move(-3 * speed, 0);
			isMovingLeft = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 2)
				randNumForMovement = 4; break;
		}
	case 3:
		if (!downCollision)
		{
			hitbox.move(0, 3 * speed);
			isMovingDown = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 3)
				randNumForMovement = 1; break;
		}
	case 4:
		if (!rightCollision)
		{
			hitbox.move(3 * speed, 0);
			isMovingRight = true;
			break;
		}
		else
		{
			randNumForMovement = std::rand() % 4 + 1;
			if (randNumForMovement == 4)
				randNumForMovement = 2; break;
		}
	default:
		break;
	}

	std::cout << "\nUP - " << upCollision << " DOWN - " << downCollision << " RIGHT - " << rightCollision << " LEFT - " << leftCollision << std::endl;*/
}

void Enemy1::collisions(Map& map)
{
	collisionChecker.setPosition(hitbox.getPosition().x - 18, hitbox.getPosition().y - 18);

	upCollision = false;
	downCollision = false;
	leftCollision = false;
	rightCollision = false;

	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;

		if (collisionChecker.getGlobalBounds().intersects(obstacleRect, intersection))
		{
			//X
			if (intersection.width < intersection.height)
			{
				if (collisionChecker.getGlobalBounds().left < obstacleRect.left)
				{
					//right
					rightCollision = true;
				}
				else
				{
					//left
					leftCollision = true;
				}
			}
			else
			{
				//Y
				if (collisionChecker.getGlobalBounds().top < obstacleRect.top)
				{
					//down
					downCollision = true;
				}
				else
				{
					//up
					upCollision = true;
				}
			}
		}
	}
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

void Enemy1::update(Player& player, Map& map)
{
	collisions(map);
	move(player);
	fieldOfView(player);
}


void Enemy1::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
// 	window.draw(view);
// 	window.draw(collisionChecker);
}
