#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy1.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball with Chipmunk2D");
	window.setFramerateLimit(60);


	Player player;
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

		player.update();

		for (size_t i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].update(player);
		}

		window.clear(sf::Color::Black);

		player.draw(window);
		
		for (size_t i = 0; i < enemyVector.size(); i++)
		{
			enemyVector[i].draw(window);
		}

		window.display();
	}


	return 0;
}