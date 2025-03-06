#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Entity
{
public:
	Entity();
	~Entity();

	virtual void initialize() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::RectangleShape getHitbox();

protected:
	sf::RectangleShape hitbox;
	sf::Color hitboxColor;

	float height;
	float widht;
	float speed;

	bool isMoovingUp = false;
	bool isMoovinDown = false;
	bool isMoovingRight = false;
	bool isMoovingLeft = false;

};
