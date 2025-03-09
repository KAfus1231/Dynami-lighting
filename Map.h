#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Map
{
private:
	friend class Player;
	static const int mapHeight = 11; // ������ ����� � �������
	static const int mapWidth = 20; // ������

	sf::String firstLayer[mapHeight]; // ������ ��������� ��� ��������� �����

	std::vector<sf::RectangleShape> mapHitbox; // �������� ��� �������� �� �����
	sf::RectangleShape hitbox;

	int tileWidth; // ���-�� �������� � ������ �� ������
	int tileHeight; // �� ������

	int totalTilesX; // ������ �� X
	int totalTilesY; // ������ �� Y

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
