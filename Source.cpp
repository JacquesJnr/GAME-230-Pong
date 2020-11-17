#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Collider.h"

using namespace std;


const int WIDTH = 1024;
const int HEIGHT = 768;
const int _ballSpeed = 500.0f;
const int _paddleSpeed = 800.0f;

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


struct Paddle
{
    sf::RectangleShape dimensions;
    sf::Vector2f postion;
    int playerNumber; //Changes what keys the player presses to move their paddle

    //Reads player input and moves the players' paddle
    void movePaddle(int playerNumber, float deltaTime) {
       
        //Player 1 Controls
        if (playerNumber == 0) {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->postion.y > 0.0f) {

                this->dimensions.setPosition(this->postion.x, this->postion.y - _paddleSpeed * deltaTime);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->postion.y < (HEIGHT - this->dimensions.getSize().y)) {

                this->dimensions.setPosition(this->postion.x, this->postion.y + _paddleSpeed * deltaTime);
            }
        }

        //Player 2 Controls
        if (playerNumber == 1) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->postion.y > 0.0f) {

                this->dimensions.setPosition(this->postion.x, this->postion.y - _paddleSpeed * deltaTime);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->postion.y < (HEIGHT - this->dimensions.getSize().y)) {

                this->dimensions.setPosition(this->postion.x, this->postion.y + _paddleSpeed * deltaTime);
            }
        }
    }

    void draw(sf::RenderWindow* window) {
        window->draw(this->dimensions);
    }
};


int main()
{

    int center_W = WIDTH / 2;
    int center_H = HEIGHT / 2;

    //Define Window dimensions and program title
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GAME 230 - Pong");
    window.setVerticalSyncEnabled(true);

    //Custom Colours
    sf::Color Purple(90, 24, 154);
    sf::Color myGreen(45, 194, 67);

    //Create Ball(s)
    Ball ball1;
    ball1.shape = sf::CircleShape(25.f);
    ball1.shape.setFillColor(Purple);
    ball1.shape.setPosition(WIDTH / 2, HEIGHT / 2 - ball1.shape.getRadius() * 2);
    ball1.velocity = sf::Vector2f(0,0);

    //Create Paddle(s)
    Paddle leftPaddle;
    leftPaddle.dimensions.setSize(sf::Vector2f(50, 150));
    leftPaddle.dimensions.setFillColor(myGreen);
    leftPaddle.dimensions.setPosition(50, HEIGHT / 2 - leftPaddle.dimensions.getSize().y);
    leftPaddle.playerNumber = 0;

    Paddle rightPaddle;
    rightPaddle.dimensions.setSize(sf::Vector2f(50, 150));
    rightPaddle.dimensions.setFillColor(myGreen);
    rightPaddle.dimensions.setPosition(924, HEIGHT/ 2 - rightPaddle.dimensions.getSize().y);
    rightPaddle.playerNumber = 1;


    //Create Dashed Lines
    sf::Vertex point;
    point.position = sf::Vector2f(WIDTH / 2, HEIGHT / 2);
    point.color = sf::Color::White;
    
    sf::VertexArray line1(sf::Points, HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        line1[i].position = sf::Vector2f(center_W - 10, i * 10);
    }

    sf::VertexArray line2(sf::Points, HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        line2[i].position = sf::Vector2f(center_W + 10, i * 10);
    }

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

        //Check player input for paddle
        leftPaddle.postion = sf::Vector2f(leftPaddle.dimensions.getPosition().x, leftPaddle.dimensions.getPosition().y);
        rightPaddle.postion = sf::Vector2f(rightPaddle.dimensions.getPosition().x, rightPaddle.dimensions.getPosition().y);


        ball1.Update(deltaTime);
        leftPaddle.movePaddle(leftPaddle.playerNumber, deltaTime);
        rightPaddle.movePaddle(rightPaddle.playerNumber, deltaTime);
        title.setString("Hello, World!");

        //Render
        window.clear(sf::Color(150, 150, 150));
        window.draw(title);
       // window.draw(line1);
       // window.draw(line2)
        leftPaddle.draw(&window);
        rightPaddle.draw(&window);
        ball1.draw(&window);
        window.display();
    }

    return 0;
};
