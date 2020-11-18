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
#include "Paddle.h"
#include "Ball.h"

using namespace std;

const int WIDTH = 1024;
const int HEIGHT = 768;
const int _ballSpeed = 500.0f;
const int _paddleSpeed = 800.0f;

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
    Ball ball(nullptr, sf::Vector2f(30, 30), sf::Vector2f(center_W ,center_H), sf::Vector2f(0, _ballSpeed));

    //Create Paddle(s)
    Paddle leftPaddle(sf::Vector2f(20,100), sf::Vector2f(50, center_H), myGreen, 0);
    Paddle rightPaddle(sf::Vector2f(20,100), sf::Vector2f(974, center_H), myGreen, 1);


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
    sf::Text ScoreL, ScoreR;
    ScoreL.setFont(font);
    ScoreR.setFont(font);
    ScoreL.setCharacterSize(48);
    ScoreR.setCharacterSize(48);
    ScoreL.setFillColor(sf::Color::White);
    ScoreR.setFillColor(sf::Color::White);
    ScoreL.setPosition(300, 50);
    ScoreR.setPosition(724, 50);

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
        ScoreL.setString("0");
        ScoreR.setString("0");
        ball.Update(deltaTime);
        leftPaddle.Update(deltaTime, _paddleSpeed);
        rightPaddle.Update(deltaTime, _paddleSpeed);
        Collider playerCollisionR = rightPaddle.GetCollider();
        Collider playerCollisionL = leftPaddle.GetCollider();
        Collider ballCollisions = ball.GetCollider();

        //ball.GetCollider().CheckCollision(playerCollisionR, 0.9f);
       // ball.GetCollider().CheckCollision(playerCollisionL, 0.9f);
        leftPaddle.GetCollider().CheckCollision(ballCollisions, 1);
        rightPaddle.GetCollider().CheckCollision(ballCollisions, 1);


        //Render
        window.clear(sf::Color());
        window.draw(ScoreL);
        window.draw(ScoreR);
        window.draw(line1);
        window.draw(line2);
        ball.draw(window);
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        window.display();
    }

    return 0;
};

