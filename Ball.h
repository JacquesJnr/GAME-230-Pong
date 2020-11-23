#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Definitions.h"
using namespace std;

class Ball
{
public:

	Ball(sf::Texture* texture ,sf::Vector2f size, sf::Vector2f position);

	sf::RectangleShape body;
	float angle = 0;
	float ballSpeed = 0;
	sf::Vector2f deltaPos;


	void Update(float deltaTime, Paddle otherPaddle);
	void draw(sf::RenderWindow& window);
};

