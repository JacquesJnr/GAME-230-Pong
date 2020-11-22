#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Paddle.h"
#include "Definitions.h"

class Ball
{
public:

	Ball(sf::Texture* texture ,sf::Vector2f size, sf::Vector2f position);

	sf::RectangleShape body;
	sf::Vector2f velocity;
	float angle  = 0.f;
	float speed = 0.f;


	void Update(float deltaTime, Paddle otherPaddle);
	void draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
};

