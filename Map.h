#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Map
{
private:
	friend class Player;
	static const int mapHeight = 11; // высота карты в плитках
	static const int mapWidth = 20; // ширина

	sf::String firstLayer[mapHeight]; // строка элементов для отрисовки карты

	std::vector<sf::RectangleShape> mapHitbox; // хитбоксы для обхектов на карте
	sf::RectangleShape hitbox;

	int tileWidth; // кол-во пикселей в плитке по ширине
	int tileHeight; // по высоте

	int totalTilesX; // плитки по X
	int totalTilesY; // плитки по Y

public:
	Map();
	~Map();

	void layerLoad(sf::String layer[]);
	void createHitbox(int x, int y, int posX, int posY);
	void initialize();
	void load();
	void update();
	void drawFirstLayer(sf::RenderWindow& window);
};
