#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "Collider.h"
#include "Paddle.h"
#include "Ball.h"
using namespace std;
using namespace sf;

int main()
{
	const int WIDTH = 1024;
	const int HEIGHT = 768;
    Vector2f playerPos = Vector2f(50, HEIGHT / 2);
    Vector2f AIPos = Vector2f( 984 , HEIGHT / 2);
    Clock clock;
    float deltaTime = 0.0f;
    float paddleSpeed = 500.0f;
    float ballSpeed = 500.0f;
    
    // Ball Size
    Vector2f ballSize = Vector2f(25.0f, 25.0f);

    // Colors
    Color purple = Color(129, 30, 168);

    // Window
    RenderWindow gameWindow(VideoMode(WIDTH, HEIGHT), "SFML Pong");
    gameWindow.setVerticalSyncEnabled(true);

    // Textures
    Texture splash, playerPaddleTexture, AI_PaddleTexture, ballTexture, background, line;
   
    if (!splash.loadFromFile("data/Textures/splash.jpg"))
        return EXIT_FAILURE;

    if (!playerPaddleTexture.loadFromFile("data/Textures/Player.png"))
        return EXIT_FAILURE;
    
    if (!AI_PaddleTexture.loadFromFile("data/Textures/AI.png"))
        return EXIT_FAILURE;

    if (!ballTexture.loadFromFile("data/Textures/Ball.png"))
        return EXIT_FAILURE;

    if (!background.loadFromFile("data/Textures/BG.png"))
        return EXIT_FAILURE;

    if (!line.loadFromFile("data/Textures/Line.png"))
        return EXIT_FAILURE;
  
    // Background
    Sprite BG(background);

    // Lines
    Sprite centerLines(line);
    centerLines.setPosition(Vector2f(WIDTH / 2, 0));

    // Fonts
    Font font;
    if (!font.loadFromFile("data/Fonts/arial.ttf"))
        return EXIT_FAILURE;
    Text text("Hello SFML", font, 50);

    // Sounds
    SoundBuffer buffer;

    // Ball(s)
    Ball ball(&ballTexture, ballSize, Vector2f(WIDTH / 2, HEIGHT / 2), Vector2f(0, 0));

    // Paddle(s)
    Paddle playerPaddle(Vector2f(30, 150), playerPos, &playerPaddleTexture, 0);
    Paddle AIPaddle(Vector2f(30, 150), AIPos, &AI_PaddleTexture, 1);
    
    // Start the game loop
    while (gameWindow.isOpen())
    {
        //Define delta time
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Process events
        Event event;
        while (gameWindow.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                gameWindow.close();
        }

        //Update Objects
        playerPaddle.Update(deltaTime, paddleSpeed);

        // Clear screen
        gameWindow.clear();
        // Draw Background
        gameWindow.draw(BG);
        // Draw Lines 
        gameWindow.draw(centerLines);
        // Draw Ball
        ball.draw(gameWindow);
        // Draw paddles
        playerPaddle.draw(gameWindow);
        AIPaddle.draw(gameWindow);
        // Update the window
        gameWindow.display();
    }
    return EXIT_SUCCESS;
}

