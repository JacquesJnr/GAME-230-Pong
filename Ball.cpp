#include "Ball.h"

Ball::Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setTexture(texture);
    body.setSize(size);
    body.setPosition(position);
}

void Ball::Update(float deltaTime, Paddle otherPaddle) {


    if (otherPaddle.playerNumber == 0) {

        if (this->body.getPosition().x - this->body.getSize().x < otherPaddle.body.getPosition().x + otherPaddle.body.getSize().x / 2 &&
            this->body.getPosition().x - this->body.getSize().x > otherPaddle.body.getPosition().x &&
            this->body.getPosition().y + this->body.getSize().y >= otherPaddle.body.getPosition().y - otherPaddle.body.getSize().y / 2 &&
            this->body.getPosition().y - this->body.getSize().y <= otherPaddle.body.getPosition().y + otherPaddle.body.getSize().y / 2)
        {
            if (this->body.getPosition().y > otherPaddle.body.getPosition().y)
                this->angle = pi - this->angle + (std::rand() % 20) * pi / 180;
            else
                this->angle = pi - this->angle - (std::rand() % 20) * pi / 180;

            this->body.setPosition(otherPaddle.body.getPosition().x + this->body.getSize().x + otherPaddle.body.getSize().x / 2 + 0.1f, this->body.getPosition().y);
        }
    }

    if (otherPaddle.playerNumber == 1) {

        if (this->body.getPosition().x + this->body.getSize().x > otherPaddle.body.getPosition().x - otherPaddle.body.getSize().x / 2 &&
            this->body.getPosition().x + this->body.getSize().x < otherPaddle.body.getPosition().x &&
            this->body.getPosition().y + this->body.getSize().y >= otherPaddle.body.getPosition().y - otherPaddle.body.getSize().y / 2 &&
            this->body.getPosition().y - this->body.getSize().y <= otherPaddle.body.getPosition().y + otherPaddle.body.getSize().y / 2)
        {
            if (this->body.getPosition().y > otherPaddle.body.getPosition().y)
                this->angle = pi - this->angle + (std::rand() % 20) * pi / 180;
            else
                this->angle = pi - this->angle - (std::rand() % 20) * pi / 180;

            this->body.setPosition(otherPaddle.body.getPosition().x + this->body.getSize().x + otherPaddle.body.getSize().x / 2 + 0.1f, this->body.getPosition().y);
        }
    }
}


void Ball::draw(sf::RenderWindow& window) {
    
    window.draw(body);
}
