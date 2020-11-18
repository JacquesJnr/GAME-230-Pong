#include "Ball.h"

Ball::Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity )
{
    body.setTexture(texture);
    body.setSize(size);
    body.setPosition(position);
    this->velocity = velocity;
}

void Ball::Update(float deltaTime) {
    
    int WIDTH = 1024;
    int HEIGHT = 768;
    
    auto position = this->body.getPosition();
    if (position.y > HEIGHT - body.getSize().y) {

        velocity.y = -abs(velocity.y);
    }
    else if(position.y < 0 - body.getSize().y)
    {
        velocity.y = abs(velocity.y);
    }
    else if(position.x > WIDTH - body.getSize().x)
    {
        velocity.x = -abs(velocity.x);
    }
    else if (position.x < 0 - body.getSize().x)
    {
        velocity.x = abs(velocity.x);
    }
    
    body.setPosition(position.x + this->velocity.x * deltaTime, position.y + this->velocity.y * deltaTime);
}


void Ball::draw(sf::RenderWindow& window) {
    
    window.draw(body);
}
