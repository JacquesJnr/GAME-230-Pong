#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Paddle
{
public:
	Paddle(sf::Vector2f size, sf::Vector2f position, sf::Texture* image, int playerNumber);
	~Paddle();

	void Update(float deltaTime, float playerSpeed);
	void draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	int playerNumber;
};
