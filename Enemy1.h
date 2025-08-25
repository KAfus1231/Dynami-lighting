#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

class Enemy1 : public Entity
{
public:
	struct Triggers
	{
		sf::Clock ClockForView;
		sf::RectangleShape viewZone;
		bool inView = false;

		bool fieldOfView(Enemy1& enemy1, Player& player);
		void draw(sf::RenderWindow& window);
	};
	
	Enemy1(Map& map);
	~Enemy1();

	void initialize() override;

	void draw(sf::RenderWindow& window) override;
	void collisions(Map& map);

	void move(Player& player);
	void movePatrol();
	void moveHarassment(Player& player);
	void update(Player& player, Map& map);
private:
	std::vector<sf::Vector2f> patrolPoints;
	int patrolPointIndex;
	bool endOfPatrol;

	sf::Clock clockForMovement;
	sf::RectangleShape collisionChecker;

	float timeForMovement;
	int randNumForMovement;

	Triggers triggers;
};