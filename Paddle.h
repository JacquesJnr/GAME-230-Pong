#pragma once
#include <SFML/Graphics.hpp>
class Paddle
{
public:
	Paddle(sf::Vector2f size, sf::Vector2f position, sf::Texture* image, int playerNumber);
	~Paddle();

	sf::RectangleShape body;

	void Update(float deltaTime, float playerSpeed);
	void draw(sf::RenderWindow& window);
	int playerNumber;
};
