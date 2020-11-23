#include "Ball.h"

Ball::Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setTexture(texture);
    body.setSize(size);
    body.setPosition(position);
}

void Ball::Update(float deltaTime, Paddle otherPaddle) {


    deltaPos = this->body.getPosition();
    float sizeX = this->body.getSize().x;
    float sizeY = this->body.getSize().y;

    float direction = ballSpeed * deltaTime;
    this->body.move(std::sin(angle) * direction, cos(angle) * direction);

    if (otherPaddle.playerNumber == 1) {

        if (deltaPos.x > otherPaddle.body.getPosition().x + sizeX * 2 &&
            deltaPos.x < otherPaddle.body.getPosition().x){

            this->angle += 180;
            
        }
    }

    if (otherPaddle.playerNumber == 0) {

        if (deltaPos.x > otherPaddle.body.getPosition().x - sizeX * 2 &&
            deltaPos.x < otherPaddle.body.getPosition().x) {

            angle += 180;

        }
    }
   
}


void Ball::draw(sf::RenderWindow& window) {
    
    window.draw(body);
}
