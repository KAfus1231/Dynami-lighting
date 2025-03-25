#include "Shaders.h"

Shaders::Shaders(sf::RenderWindow& window)
{
	load(window);
	initialize(window);
}

Shaders::~Shaders()
{
}

void Shaders::load(sf::RenderWindow& window)
{
	try
	{
		if (!lampShader.loadFromFile("assets/shaders/playerLampShader.frag", sf::Shader::Fragment))
			throw "void::Shaders::load::playerLampShader.frag";
	}
	catch (const char* errMsg)
	{
		std::cerr << errMsg << std::endl;
	}
}

void Shaders::initialize(sf::RenderWindow& window)
{
	darkness.create(1600, 1600);
	darkness.clear(sf::Color(0, 0, 0, 220));
	darknessSprite.setTexture(darkness.getTexture());

	lightTexture.create(1600, 1600);
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> Shaders::getRectEdges(const sf::FloatRect& rect)
{
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges;

	sf::Vector2f topLeft(rect.left, rect.top);
	sf::Vector2f topRight(rect.left + rect.width, rect.top);
	sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);
	sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);

	edges.push_back({ topLeft, topRight }); // ВЕРХ
	edges.push_back({ bottomLeft, bottomRight }); // НИЗ
	edges.push_back({ topLeft, bottomLeft }); // ЛЕВАЯ СТЕНКА
	edges.push_back({ topRight, bottomRight }); // ПРАВАЯ СТЕНКА

	return edges;
}

bool Shaders::raySegmentIntersection(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDir,
	const sf::Vector2f& segA, const sf::Vector2f& segB, sf::Vector2f& intersection)
{
	sf::Vector2f segDir = segB - segA;
	float rxs = rayDir.x * segDir.y - rayDir.y * segDir.x;
	if (fabs(rxs) < 1e-8f)
		return false; // Параллельны, пересечения нет.

	sf::Vector2f diff = segA - rayOrigin;
	float t = (diff.x * segDir.y - diff.y * segDir.x) / rxs;
	float u = (diff.x * rayDir.y - diff.y * rayDir.x) / rxs;

	if (t >= 0 && u >= 0 && u <= 1)
	{
		intersection = rayOrigin + rayDir * t;
		return true;
	}
	return false;
}

void Shaders::dynamicLighting(sf::RenderWindow& window, sf::Vector2f startPos, Map& map)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::Vector2f baseDir = mousePos - startPos;

	float length = sqrt(baseDir.x * baseDir.x + baseDir.y * baseDir.y); // НОРМАЛИЗАЦИЯ
	if (length > 0)
		baseDir /= length;

	// Угол раскрытия фонарика (в радианах)
	float flashlightAngle = 60.0f * 3.14159265f / 180.f;
	int rayCount = 50; // Количество лучей (чем больше, тем плавнее)
	float flashlightLength = 250.0f; // Дальность лучей

	polygon = sf::VertexArray(sf::TriangleFan);
	polygon.append(sf::Vertex(startPos, sf::Color(255, 255, 200, 20))); // Центр фонаря

	std::vector<sf::Vector2f> intersectionPoints;

	for (int i = 0; i <= rayCount; ++i)
	{
		float angleOffset = (i / float(rayCount) - 0.5f) * flashlightAngle;
		float cosA = cos(angleOffset);
		float sinA = sin(angleOffset);

		// Вращаем базовый вектор
		sf::Vector2f rayDir(baseDir.x * cosA - baseDir.y * sinA, baseDir.x * sinA + baseDir.y * cosA);

		sf::Vector2f closestIntersection = startPos + rayDir * flashlightLength;
		float closestDist = flashlightLength;

		for (const auto& wall : map.mapHitbox)
		{
			if (!wall.getGlobalBounds().intersects(sf::FloatRect(startPos.x - flashlightLength, startPos.y - flashlightLength, flashlightLength * 2, flashlightLength * 2)))
				continue;

			sf::FloatRect rect = wall.getGlobalBounds();
			auto edges = getRectEdges(rect);
			for (auto& edge : edges)
			{
				sf::Vector2f intersection;
				if (raySegmentIntersection(startPos, rayDir, edge.first, edge.second, intersection))
				{
					float dist = hypot(intersection.x - startPos.x, intersection.y - startPos.y);
					if (dist < closestDist)
					{
						closestDist = dist;
						closestIntersection = intersection;
					}
				}
			}
		}

		intersectionPoints.push_back(closestIntersection);
	}

	// Добавляем точки пересечений
	for (auto& point : intersectionPoints)
	{
		polygon.append(sf::Vertex(point, sf::Color(0, 0, 0, 0)));
	}


	//---------------------------------------------------СЦЕНА СВЕТА-----------------------------------------------------------
}

void Shaders::update(sf::RenderWindow& window, Player& player, Map& map)
{
	dynamicLighting(window, player.getHitboxPosition(), map);
}

void Shaders::draw(sf::RenderWindow& window, Player& player)
{
	darkness.clear(sf::Color(0, 0, 0, 220));
	darkness.draw(polygon, sf::BlendNone);
	darkness.display();

	window.draw(darknessSprite);
}