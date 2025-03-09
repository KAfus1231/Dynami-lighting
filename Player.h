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

	void move(Map& map);
	void collisions(Map& map);
	void update(Map& map);
private:
	bool upCollision = false;
	bool downCollision = false;
	bool rightCollision = false;
	bool leftCollision = false;
};
