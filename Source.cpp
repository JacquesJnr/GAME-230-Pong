#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace std;


const int WIDTH = 1024;
const int HEIGHT = 768;
const int SPEED = 500.0f;

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    void Update(float deltaTime) {

        auto position = this->shape.getPosition();
        this->shape.setPosition(position.x + this->velocity.x * deltaTime, position.y + this->velocity.y * deltaTime);


        //Check if the ball touches bounds of window
        if (position.y > HEIGHT - this->shape.getRadius() * 2) {
            this->velocity.y = -abs(this->velocity.y);
        }

        if (position.y <= 0.0f) {
            this->velocity.y = abs(this->velocity.y);
        }

        if (position.x > WIDTH - this->shape.getRadius() * 2) {
            this->velocity.x = -abs(this->velocity.x);
        }

        if (position.x <= 0.0f) {
            this->velocity.x = abs(this->velocity.x);
        }
    }

    void draw(sf::RenderWindow* window) {
        window->draw(this->shape);
    }
};


int main()
{
    //Define Window dimensions and program title
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GAME 230 - Pong");
    window.setVerticalSyncEnabled(true);

    //Custom Colours
    sf::Color Purple(90, 24, 154);
    sf::Color myGreen(45, 194, 67);

    Ball ball1;
    ball1.shape = sf::CircleShape(25.f);
    ball1.shape.setFillColor(Purple);
    ball1.shape.setPosition(WIDTH / 2, HEIGHT / 2);
    ball1.velocity = sf::Vector2f(SPEED, SPEED);

    //Create Paddle
    sf::RectangleShape paddle;
    paddle.setSize(sf::Vector2f(50,150));
    paddle.setFillColor(myGreen);
    paddle.setPosition(100, 100);
    
    //Load Font
    sf::Font font;
    if (!font.loadFromFile("data/Fonts/OpenSans-Regular.ttf")) {
        return 1;
    }

    //Position Text
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(12);
    title.setFillColor(sf::Color::Red);
    title.setPosition(0, 40);

    //Define clock
    sf::Clock clock;
    float deltaTime = 0.0f;


    //Update
    while (window.isOpen())
    {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball1.Update(deltaTime);
        title.setString("Hello, World!");

        //Render
        window.clear();
        window.draw(title);
        window.draw(paddle);
        ball1.draw(&window);
        window.display();
    }

    return 0;
}
