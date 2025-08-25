#include "Player.h"
#include <cmath>

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

	hitboxColor = sf::Color(181, 70, 70);
	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setOrigin(widht / 2, height / 2);
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(320, 160);

	cameraHitbox.setOrigin(640, 360);
	cameraHitbox.setSize(sf::Vector2f(1280, 720));
	cameraHitbox.setFillColor(sf::Color::Transparent);
	cameraHitbox.setOutlineColor(sf::Color::Magenta);
	cameraHitbox.setOutlineThickness(2);

	lamp.setRadius(150);
	lamp.setFillColor(sf::Color(255, 255, 200, 128));
	lamp.setOrigin(75, 75);
	lamp.setPosition(hitbox.getPosition());
}

void Player::move(Map& map)
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingRight = false;
	isMovingLeft = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isMovingDown)
	{
		hitbox.move(0, -3 * speed);
		isMovingUp = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isMovingRight)
	{
		hitbox.move(-3 * speed, 0);
		isMovingLeft = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isMovingUp)
	{
		hitbox.move(0, 3 * speed);
		isMovingDown = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isMovingLeft)
	{
		hitbox.move(3 * speed, 0);
		isMovingRight = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		hitbox.rotate(5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		hitbox.rotate(-5);
	}
}

void Player::collisions(Map& map)
{
	sf::FloatRect playerRect = hitbox.getGlobalBounds();
	const float tolerance = 2.0f; // Если пересечение меньше 2 пикселей, игнорируем его

	upCollision = false;
	downCollision = false;
	leftCollision = false;
	rightCollision = false;

	// X
	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;
		if (playerRect.intersects(obstacleRect, intersection))
		{
			// Если пересечение по оси X меньше, чем по Y, обрабатываем горизонтально
			if (intersection.width < intersection.height && intersection.width > tolerance)
			{
				if (playerRect.left < obstacleRect.left)
				{
					hitbox.move(-intersection.width, 0);
					rightCollision = true;
				}
				else
				{
					hitbox.move(intersection.width, 0);
					leftCollision = true;
				}
				playerRect = hitbox.getGlobalBounds();
			}
		}
	}

	// Y
	// Обновляем playerRect после горизонтальной коррекции
	playerRect = hitbox.getGlobalBounds();
	for (const auto& mapHitbox : map.mapHitbox)
	{
		sf::FloatRect obstacleRect = mapHitbox.getGlobalBounds();
		sf::FloatRect intersection;
		if (playerRect.intersects(obstacleRect, intersection))
		{
			if (intersection.height < intersection.width && intersection.height > tolerance)
			{
				if (playerRect.top < obstacleRect.top)
				{
					hitbox.move(0, -intersection.height);
					downCollision = true;
				}
				else
				{
					hitbox.move(0, intersection.height);
					upCollision = true;
				}
				playerRect = hitbox.getGlobalBounds();
			}
		}
	}
}

sf::View Player::camera(sf::View view)
{
	int offset = 10;
	
	float leftBorder = view.getCenter().x - offset;
	float rightBorder = view.getCenter().x + offset;

	float upBorder = view.getCenter().y - offset;
	float downBorder = view.getCenter().y + offset;

	float smoothFactor = 0.1f;

	// Позиция игрока
	float playerX = hitbox.getPosition().x;
	float cameraX = view.getCenter().x;

	float playerY = hitbox.getPosition().y;
	float cameraY = view.getCenter().y;

	if (playerX < leftBorder)
	{
		cameraX = playerX + offset;
	}
	else if (playerX > rightBorder)
	{
		cameraX = playerX - offset;
	}

	if (playerY < upBorder)
	{
		cameraY = playerY + offset;
	}
	else if (playerY > downBorder)
	{
		cameraY = playerY - offset;
	}

	float newCameraX = cameraX * smoothFactor + view.getCenter().x * (1 - smoothFactor);
	float newCameraY = cameraY * smoothFactor + view.getCenter().y * (1 - smoothFactor);

	cameraHitbox.setPosition(hitbox.getPosition());
	view.setSize(640, 360);

	view.setCenter(newCameraX, newCameraY); // Камера двигается только по X
	/*view.setRotation(hitbox.getRotation());*/

	return view;
}

void Player::lantern(sf::RenderWindow& window, Map& map, Shaders& shader)
{
	shader.dynamicLighting(window, hitbox.getPosition(), map);
}

void Player::update(Map &map, sf::RenderWindow& window, Shaders& shader)
{
	collisions(map);
	move(map);
	lantern(window, map, shader);

	view = camera(view);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
	window.setView(view);
}

sf::Vector2f Player::getViewCenter()
{
	return view.getCenter();
}

sf::ConvexShape Player::getLantern()
{
	return flashlight;
}

sf::CircleShape Player::getLamp()
{
	return lamp;
}

