#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy1.h"
#include "Map.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball with Chipmunk2D");
	window.setFramerateLimit(60);

	Player player;
	Map map;
	std::vector<Enemy1> enemyVector;

	for (size_t i = 0; i < 2; i++)
	{
		Enemy1 enemy1;
		enemyVector.push_back(enemy1);
	}



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}


		player.update(map);
		map.update();

		window.clear(sf::Color::Black);
		player.draw(window);

		for (size_t i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].update(player, map);
		}

		for (size_t i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].draw(window);
		}
		map.drawFirstLayer(window);
		window.display();
	}
	return 0;
}