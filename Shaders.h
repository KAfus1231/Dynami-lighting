#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Shaders
{
public:
	Shaders(sf::RenderWindow& window);
	~Shaders();

	void initialize(sf::RenderWindow& window);
	void load(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, Player& player, Map& map);
	void draw(sf::RenderWindow& window, Player& player);
	void dynamicLighting(sf::RenderWindow& window, sf::Vector2f startPos, Map& map);

	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getRectEdges(const sf::FloatRect& rect);

	bool raySegmentIntersection(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDir,
		const sf::Vector2f& segA, const sf::Vector2f& segB,
		sf::Vector2f& intersection);
private:
	friend class Player;
	friend class Enemy1;

	sf::Shader lampShader;
	sf::VertexArray polygon;

	sf::RenderTexture darkness;
	sf::Sprite darknessSprite;

	sf::RenderTexture lightTexture;
};
