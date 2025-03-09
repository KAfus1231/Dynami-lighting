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
	widht = 16.0f;
	height = 16.0f;

	hitboxColor = sf::Color::Green;
	hitbox = sf::RectangleShape(sf::Vector2f(widht, height));
	hitbox.setFillColor(hitboxColor);
	hitbox.setPosition(0, 0);
}

void Player::move(Map& map)
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingRight = false;
	isMovingLeft = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isMovingDown && !downCollision)
	{
		hitbox.move(0, -3 * speed);
		isMovingUp = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isMovingRight && !leftCollision)
	{
		hitbox.move(-3 * speed, 0);
		isMovingLeft = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isMovingUp && !upCollision)
	{
		hitbox.move(0, 3 * speed);
		isMovingDown = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isMovingLeft && !rightCollision)
	{
		hitbox.move(3 * speed, 0);
		isMovingRight = true;
	}
	
	{
		system("cls");
		std::cout << "W - " << isMovingUp << " A - " << isMovingLeft << " S - " << isMovingDown << " D - " << isMovingRight << std::endl;
		std::cout << direction.x << " - " << direction.y;
		std::cout << "\nUP - " << upCollision << " DOWN - " << downCollision << " RIGHT - " << rightCollision << " LEFT - " << leftCollision << std::endl;
	}

}

void Player::collisions(Map& map)
{
	direction = sf::Vector2f(0, 0);

	upCollision = false;
	downCollision = false;
	rightCollision = false;
	leftCollision = false;

	for (const auto& mapHitbox : map.mapHitbox)
	{
		float hitboxCenterX = hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width / 2;
		float hitboxCenterY = hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height / 2;
		float mapHitboxCenterX = mapHitbox.getGlobalBounds().left + mapHitbox.getGlobalBounds().width / 2;
		float mapHitboxCenterY = mapHitbox.getGlobalBounds().top + mapHitbox.getGlobalBounds().height / 2;

		float deltaX = hitboxCenterX - mapHitboxCenterX;
		float deltaY = hitboxCenterY - mapHitboxCenterY;

		if (hitbox.getGlobalBounds().intersects(mapHitbox.getGlobalBounds()))
		{
			//direction = sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2) -
			//	sf::Vector2f(mapHitbox.getPosition().x + mapHitbox.getSize().x / 2, mapHitbox.getPosition().y + mapHitbox.getSize().y / 2); // вектор столкновения игрока и объекта
			//direction = NormalizeVector(direction); // нормализация вектора столкновения

			//direction.x > 0 ? leftCollision = true : rightCollision = true;
			//direction.y > 0 ? downCollision = true : upCollision = true;

			if (abs(deltaX) > abs(deltaY) && deltaX > 0) 
			{
				leftCollision = true; 
			}
			else if (abs(deltaX) > abs(deltaY) && deltaX < 0)
			{
				rightCollision = true; 
			}
			else if (abs(deltaX) <= abs(deltaY) && deltaY > 0) 
			{
				downCollision = true; 
			}
			else {
				upCollision = true;
			}
			std::cout << "collision" << std::endl;
		}
	}
}

void Player::update(Map &map)
{
	move(map);
	collisions(map);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(hitbox);
}