#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy1.h"
#include "Map.h"
#include "Shaders.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

int main() {
	setlocale(0, "");
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball with Chipmunk2D");
	window.setFramerateLimit(60);

	sf::Clock clockForSpawn; // таймер дл€ создани€ врагов

	//-----------------------------------------HEADERS------------------------------------

	Player player;
	Map map;
	std::vector<Enemy1> enemyVector;
	Shaders shaders(window);
	for (size_t i = 0; i < 1; i++)
	{
		Enemy1 enemy1(map);
		enemyVector.push_back(enemy1);
	}

	// интервал спавна врагов
	const float spawnInterval = 2.0f; // интервал спавна врагов в секундах
	clockForSpawn.restart(); // «апуск таймера спавна

	//----------------------------------------GAMELOOP------------------------------------

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//-----------------------------------------CONSTS---------------------------------------

		static int enemyCount = 0; // предел обработки врагов
		if (clockForSpawn.getElapsedTime().asSeconds() >= spawnInterval && enemyCount < enemyVector.size())
		{
			clockForSpawn.restart();

			enemyCount++; // если таймер сработал, то предел стал выше
		}

		//-----------------------------------------UPDATE----------------------------------------

		player.update(map, window, shaders);

		for (size_t i = 0; i < enemyCount; i++)
		{
			enemyVector[i].update(player, map);
		}

		map.update();
		//-----------------------------------------DRAW------------------------------------------

		window.clear(sf::Color(102, 97, 97));

		for (size_t i = 0; i < enemyCount; i++)
		{
			enemyVector[i].draw(window);
		}

		map.drawFirstLayer(window);
		player.draw(window);
		shaders.draw(window);

		window.display();
	}
	return 0;
}