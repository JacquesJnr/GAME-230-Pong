#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void Move(float delta_x, float delta_y) { body.move(delta_x, delta_y); }

	bool CheckCollision(Collider& other, float pushAway);
	sf::Vector2f GetPosition() {return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;

};

