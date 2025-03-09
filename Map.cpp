#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(32), tileHeight(32), totalTilesX(0), totalTilesY(0)
{
	initialize();
	load();
}

Map::~Map() {}

void Map::initialize() // ����� 
{
	// ������ ����!! ��� � ���������
	firstLayer[0] =  "                    ";
	firstLayer[1] =  "                    ";
	firstLayer[2] =  "                    ";
	firstLayer[3] =  "                    ";
	firstLayer[4] =  "                    ";
	firstLayer[5] =  "           0        ";
	firstLayer[6] =  "                    ";
	firstLayer[7] =  "                    ";
	firstLayer[8] =  "                    ";
	firstLayer[9] =  "                    ";
	firstLayer[10] = "                    ";
	
}

void Map::load()
{
	layerLoad(firstLayer);
}

void Map::layerLoad(sf::String layer[])
{
	for (int i = 0; i < mapHeight; i++) // ���������� �� ��������
		for (int j = 0; j < mapWidth; j++) // � ��� �� ������
		{
			switch (layer[i][j])
			{
			case('0'): // ���
				createHitbox(tileWidth, tileHeight, j * tileWidth, i * tileHeight);
				
			}
		}
}

void Map::update() // �������������� ������ � �����
{

}

void Map::createHitbox(int x, int y, int posX, int posY)
{
	std::cout << "CreateHitbox Working!" << std::endl;
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);
	hitbox.setSize(sf::Vector2f(x, y));
	hitbox.setPosition(posX,posY);
	mapHitbox.push_back(hitbox);
}

// ��������� ������� ���� �����
void Map::drawFirstLayer(sf::RenderWindow& window)
{
	for (const auto& hitbox : mapHitbox)
		window.draw(hitbox);
}


