#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Map
{
public:
	Map();
	~Map();

	void layerLoad(sf::String layer[]);
	void createHitbox(int x, int y, int posX, int posY);
	void initialize();
	void load();
	void update();
	void drawFirstLayer(sf::RenderWindow& window);
	sf::Vector2f getEnemyStartPosition();
private:
	friend class Enemy1;
	friend class Player;
	friend class Shaders;

	static const int mapHeight = 50; // высота карты в плитках
	static const int mapWidth = 50; // ширина

	sf::String firstLayer[mapHeight]; // строка элементов для отрисовки карты
	std::vector<sf::Vector2f> enemiesPositions;
	std::vector<sf::RectangleShape> mapHitbox; // хитбоксы для обхектов на карте

	sf::RectangleShape hitbox;

	int tileWidth; // кол-во пикселей в плитке по ширине
	int tileHeight; // по высоте

	int totalTilesX; // плитки по X
	int totalTilesY; // плитки по Y
};
