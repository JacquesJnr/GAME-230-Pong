#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "Definitions.h"
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
    float ballAngle = 0.f;
    Vector2f ballPos;
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
    SoundBuffer sound1, sound2, sound3;

    if (!sound1.loadFromFile(SOUND_PATH "ballHit.wav"))
        return EXIT_FAILURE;

    if (!sound2.loadFromFile(SOUND_PATH "gainPoint.wav"))
        return EXIT_FAILURE;

    if (!sound3.loadFromFile(SOUND_PATH "losePoint.wav"))
        return EXIT_FAILURE;
    
    Sound ballHit;
    Sound gainPoint, losePoint;

    ballHit.setBuffer(sound1);
    gainPoint.setBuffer(sound2);
    gainPoint.setVolume(40);
    losePoint.setBuffer(sound3);
    losePoint.setVolume(40);

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

    // Press ESC 
    Text pressEsc;
    pressEsc.setFont(font);
    pressEsc.setString("Press ESC to close the game");
    pressEsc.setCharacterSize(14);
    pressEsc.setPosition(Vector2f(WIDTH - 170, 10));
    pressEsc.setFillColor(Color(255, 255, 255, 100));

    // Press R
    Text pressR;
    pressR.setFont(font);
    pressR.setString("Press R to restart the game");
    pressR.setCharacterSize(14);
    pressR.setPosition(Vector2f(WIDTH - 170, 25));
    pressR.setFillColor(Color(255,255,255, 100));

    // Pause Menu
    Sprite arrowMessage(keys);
    arrowMessage.setPosition(320.0f, 300.0f);
    
    Text debug;
    debug.setFont(font);
    debug.setCharacterSize(20);
    debug.setPosition(centerScreen);
    debug.setFillColor(sf::Color::Red);
    debug.setString("debug");

    Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(35);
    pauseMessage.setPosition(0.f, 0.f);
    pauseMessage.setFillColor(sf::Color::White);

    pauseMessage.setString("Welcome to SFML pong!\nPress Up or Down keys start the game");

    // Ball(s)
    Ball ball(&ballTexture, ballSize, centerScreen);

    sf::Clock AITime;
    const Time AITimer = seconds(0.5f);
    float AIpaddleSpeed = 0.f;

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

                    // Reset ball angle
                    do
                    {
                        ballAngle = (std::rand() % 360) * 2 * pi / 360;
                    } while (std::abs(std::cos(ballAngle)) < 0.7f);

                }
            }
        }

        if (isPlaying) 
        {
            
        
            if (alpha > 0) {
                overlay.setColor(sf::Color(255, 255, 255, alpha));
                alpha--;
            }

            float factor = ball.ballSpeed * deltaTime;
            ball.body.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

            //Move the paddles
            playerPaddle.Update(deltaTime, paddleSpeed);

            if (((AIpaddleSpeed < 0.f) && (AIPaddle.body.getPosition().y - paddleSize.y / 2 > 5.f)) ||
                ((AIpaddleSpeed > 0.f) && (AIPaddle.body.getPosition().y + paddleSize.y / 2 < HEIGHT - 5.f)))
            {
                AIPaddle.body.move(0.f, AIpaddleSpeed * deltaTime);
            }

            if (AITime.getElapsedTime() > AITimer)
            {
                AITime.restart();
                if (ball.body.getPosition().y + ball.body.getSize().y > AIPaddle.body.getPosition().y + paddleSize.y / 2)
                    AIpaddleSpeed = paddleSpeed - 100;
                else if (ball.body.getPosition().y - ball.body.getSize().y < AIPaddle.body.getPosition().y - paddleSize.y / 2)
                    AIpaddleSpeed = -paddleSpeed - 100;
                else
                    AIpaddleSpeed = 0.f;
            }

            // Check collisions between the ball and the screen
            if (ball.body.getPosition().x - ballSize.x < 0.f)
            {
                AIScore.setString(to_string(_AIScore += 1));
                losePoint.play();
                ball.body.setPosition(centerScreen);
                ballAngle = (rand() % 360 * 2 * pi / 360);
            }
            
            if (ball.body.getPosition().x - ballSize.x >= WIDTH)
            {
                playerScore.setString(to_string(_playerScore += 1));
                gainPoint.play();
                ball.body.setPosition(centerScreen);
                do
                {
                    ballAngle = (rand() % 360 * 2 * pi / 360);

                } while (abs(cos(ballAngle)) < 0.7f);
            }

            if (ball.body.getPosition().y - ballSize.y < 0.f)
            {
                ballHit.setPitch(0.7);
                ballHit.play();
                ballAngle = -ballAngle;
                ball.body.setPosition(ball.body.getPosition().x, ballSize.x + 0.1f);
            }

            if (ball.body.getPosition().y + ballSize.x > HEIGHT)
            {
                ballHit.setPitch(0.9);
                ballHit.play();
                ballAngle = -ballAngle;
                ball.body.setPosition(ball.body.getPosition().x, HEIGHT - ballSize.x - 0.1f);
            }

            // Check if ball is colliding with paddles
            // Players Paddle
            if (ball.body.getPosition().x - ballSize.x < playerPaddle.body.getPosition().x + 10 &&
                ball.body.getPosition().x + ballSize.x > playerPaddle.body.getPosition().x &&
                ball.body.getPosition().y + ballSize.y >= playerPaddle.body.getPosition().y - paddleSize.y / 2 &&
                ball.body.getPosition().y - ballSize.y <= playerPaddle.body.getPosition().y + paddleSize.y / 2)
            {
                if (ball.body.getPosition().y > playerPaddle.body.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

                ballHit.play();
                ball.body.setPosition(playerPaddle.body.getPosition().x + ballSize.x + paddleSize.x / 2 + 0.1f, ball.body.getPosition().y);
            }

            // AI Paddle
            if (ball.body.getPosition().x + ballSize.x > AIPaddle.body.getPosition().x - paddleSize.x / 2 &&
                ball.body.getPosition().x + ballSize.x < AIPaddle.body.getPosition().x &&
                ball.body.getPosition().y + ballSize.y >= AIPaddle.body.getPosition().y - paddleSize.y / 2 &&
                ball.body.getPosition().y - ballSize.y <= AIPaddle.body.getPosition().y + paddleSize.y / 2)
            {
                if (ball.body.getPosition().y > AIPaddle.body.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

                ballHit.play();
                ball.body.setPosition(AIPaddle.body.getPosition().x - ballSize.x - paddleSize.x / 2 - 0.1f, ball.body.getPosition().y);
            }

            // Restart
            if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::R))) {

                isPlaying = false;
            }
            // Declare Winner
            if (_AIScore == 5 || _playerScore == 5) {
                isPlaying = false;
            }
           
        }

        // Clear screen
        gameWindow.clear();

        // Draw Background
        gameWindow.draw(BG);
        gameWindow.draw(overlay);

        if (isPlaying) {
            // Draw Lines 
            gameWindow.draw(centerLines);
            // Draw Text
            gameWindow.draw(pressEsc);
            gameWindow.draw(pressR);
            // Draw Scores
            gameWindow.draw(playerScore);
            gameWindow.draw(AIScore);
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
