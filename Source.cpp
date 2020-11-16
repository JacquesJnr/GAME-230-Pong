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


int main()
{
    const int WIDTH = 1024;
    const int HEIGHT = 768;
    const int SPEED = 500.0f;

    //Define Window dimensions and program title
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GAME 230 - Pong");
    window.setVerticalSyncEnabled(true);

    //Load Font
    sf::Font font;
    if (!font.loadFromFile("data/Fonts/OpenSans-Regular.ttf")) {
        return 1;
    }

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(12);
    title.setFillColor(sf::Color::Red);
    title.setPosition(0, 40);

    //Define shape, position & colour
    sf::CircleShape shape(100.f);
    shape.setPosition(412, 284);
    sf::Color Purple(90, 24, 154);
    shape.setFillColor(Purple);
    sf::Clock clock;
    float deltaTime = 0.0f;
    sf::Vector2f velocity(0, SPEED);


    //Update
    while (window.isOpen())
    {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        cout << deltaTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto position = shape.getPosition();
        shape.setPosition(position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime);

        if (position.y > HEIGHT - shape.getRadius() * 2) {
            velocity.y = -SPEED;
        }

        if (position.y <= 0.0f) {
            velocity.y = SPEED;
        }

        //Render
        window.clear();
        window.draw(title);
        window.draw(shape);
        window.display();
    }

    return 0;
}
