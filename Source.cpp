#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "Definitions.h"
#include "Collider.h"
#include "Paddle.h"
#include "Ball.h"
using namespace std;
using namespace sf;


int main()
{
    Vector2f playerPos(50, HEIGHT / 2);
    Vector2f AIPos( 984 , HEIGHT / 2);
    Vector2f centerScreen(WIDTH / 2, HEIGHT / 2);
    Vector2f playerScorePos(WIDTH / 4, 50);
    Vector2f AIScorePos(WIDTH - 256, 50);
    Clock clock;
    float deltaTime = 0.0f;
    Time currentTime;

    float paddleSpeed = 500.0f;
    float ballSpeed = 500.0f;
    int _playerScore = 0;
    int _AIScore = 0;
    int alpha = 255;
   
    // Window
    RenderWindow gameWindow(VideoMode(WIDTH, HEIGHT), "SFML Pong", sf::Style::Titlebar | sf::Style::Close);
    gameWindow.setVerticalSyncEnabled(true);

    // Ball Size
    Vector2f ballSize(25.0f, 25.0f);

    // Paddle Size
    Vector2f paddleSize(30, 150);

    // Textures
    Texture splash, playerPaddleTexture, AI_PaddleTexture, ballTexture, background, line, keys, greyOverlay;
   
    if (!splash.loadFromFile("data/Textures/splash.jpg"))
        return EXIT_FAILURE;

    if (!playerPaddleTexture.loadFromFile( TEXTURE_PATH "Player.png"))
        return EXIT_FAILURE;
    
    if (!AI_PaddleTexture.loadFromFile( TEXTURE_PATH "AI.png"))
        return EXIT_FAILURE;

    if (!ballTexture.loadFromFile( TEXTURE_PATH "Ball.png"))
        return EXIT_FAILURE;

    if (!background.loadFromFile( TEXTURE_PATH "BG.png"))
        return EXIT_FAILURE;

    if (!line.loadFromFile(TEXTURE_PATH "Line.png"))
        return EXIT_FAILURE;

    if (!keys.loadFromFile(TEXTURE_PATH "Keys.png"))
        return EXIT_FAILURE;

    if (!greyOverlay.loadFromFile(TEXTURE_PATH "PauseOverlay.png"))
        return EXIT_FAILURE;
  
    // Sounds
    SoundBuffer buffer;

    // Backgrounds
    Sprite BG(background);
    Sprite overlay(greyOverlay);
    overlay.setColor(Color(255, 255, 255, alpha));

    // Lines
    Sprite centerLines(line);
    centerLines.setPosition(Vector2f(WIDTH / 2, 0));

    // Scores
    Font font;
    if (!font.loadFromFile(FONT_PATH "Poiret.ttf"))
        return EXIT_FAILURE;

    Text playerScore(to_string(_playerScore), font, 60);
    playerScore.setPosition(playerScorePos);

    Text AIScore(to_string(_AIScore), font, 60);
    AIScore.setPosition(AIScorePos);

    // Pause Menu
    Sprite arrowMessage(keys);
    arrowMessage.setPosition(320.0f, 300.0f);

    Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(256.0f, 150.f);
    pauseMessage.setFillColor(sf::Color::White);

    pauseMessage.setString("Welcome to SFML pong!\nPress the arrow keys start the game");

    // Ball(s)
    Ball ball(&ballTexture, ballSize, centerScreen, Vector2f(0, 0));

    // Paddle(s)
    Paddle playerPaddle(paddleSize, playerPos, &playerPaddleTexture, 0);
    Paddle AIPaddle(paddleSize, AIPos, &AI_PaddleTexture, 1);
    
    bool isPlaying = false;
    // Start the game loop
    while (gameWindow.isOpen())
    {
        //Define delta time
        deltaTime = clock.getElapsedTime().asSeconds();
        currentTime = clock.getElapsedTime();
        clock.restart();

        // Process events
        Event event;
        while (gameWindow.pollEvent(event))
        {
            // Close window
            if ((event.type == Event::Closed) || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                gameWindow.close();
                break;
            }

            // Space key pressed: play
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) || (event.key.code == sf::Keyboard::Down))
            {
                if (!isPlaying) 
                {

                    isPlaying = true;
                    clock.restart();

                    //Reset ball and paddle positions
                    playerPaddle.body.setPosition(playerPos);
                    AIPaddle.body.setPosition(AIPos);
                    ball.body.setPosition(centerScreen);
                }

            }
        }

        if (isPlaying) 
        {
           // float deltaTime = clock.restart().asSeconds();

            if (alpha > 0) {
                overlay.setColor(sf::Color(255, 255, 255, alpha));
                alpha--;
            }

            //Update Objects
            playerPaddle.Update(deltaTime, paddleSpeed);

            
        }

        // Clear screen
        gameWindow.clear();

        // Draw Background
        gameWindow.draw(BG);
        gameWindow.draw(overlay);

        if (isPlaying) {
           
            // Draw Scores
            gameWindow.draw(playerScore);
            gameWindow.draw(AIScore);
            // Draw Lines 
            gameWindow.draw(centerLines);
            // Draw paddles
            playerPaddle.draw(gameWindow);
            AIPaddle.draw(gameWindow);
            // Draw Ball
            ball.draw(gameWindow);
        }
        else
        {
            // Draw Pause Menu
            gameWindow.draw(pauseMessage);
            gameWindow.draw(arrowMessage);
        }

        // Update the window
        gameWindow.display();
    }
    return EXIT_SUCCESS;
}

