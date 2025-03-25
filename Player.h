#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Map.h"

class Map;

class Player : public Entity
{
public:
	Player();
	~Player();

	void initialize() override;
	void draw(sf::RenderWindow& window) override;
	void collisions(Map& map);

	void move(Map& map);
	void update(Map& map, sf::RenderWindow& window);
	sf::View camera(sf::View view);
	void lantern(sf::RenderWindow& window);

	sf::Vector2f getViewCenter();
	sf::ConvexShape getLantern();
	sf::CircleShape getLamp();
private:
	sf::RectangleShape cameraHitbox;
	sf::ConvexShape flashlight;
	sf::CircleShape lamp;
	sf::View view;
};
