#pragma once
#include <SFML/Graphics.hpp>
class Paddle
{
	Paddle(sf::Vector2f size, sf::Vector2f position);

	void draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};
