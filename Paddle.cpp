#include "Paddle.h"
#include "Collider.h"

Paddle::Paddle(sf::Vector2f size, sf::Vector2f position, sf::Texture* image, int playerNumber)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
    body.setTexture(image);
    this->playerNumber = playerNumber;
}

Paddle::~Paddle()
{
}


void Paddle::Update(float deltaTime, float playerSpeed)
{
	//Player 1 Controls

    if (this->playerNumber == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->body.getPosition().y > 0.0f) {

            this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y - playerSpeed * deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->body.getPosition().y < (768 - (this->body.getSize().y / 2))) {

            this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y + playerSpeed * deltaTime);
        }
    }
    
    else if (this->playerNumber == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->body.getPosition().y > 0.0f) {

            this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y - playerSpeed * deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->body.getPosition().y < (768 - (this->body.getSize().y / 2))) {

            this->body.setPosition(this->body.getPosition().x, this->body.getPosition().y + playerSpeed * deltaTime);
        }
    }
    
}

void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
