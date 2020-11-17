#pragma once
#include <SFML/Graphics.hpp>
class Paddle
{
public:
	Paddle(sf::Vector2f size, sf::Vector2f position);
	~Paddle();

	void draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};
