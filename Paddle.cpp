#include "Paddle.h"
#include "Collider.h"

Paddle::Paddle(sf::Vector2f size, sf::Vector2f position) 
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
}


void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
