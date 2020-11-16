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
    //Define Window dimensions and program title
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GAME 230 - Pong");
    window.setVerticalSyncEnabled(true);

    //Define shape as circle
    sf::CircleShape shape(100.f);
    //Set the circle Position
    shape.setPosition(412, 284);
    //Define Purple
    sf::Color Purple(90, 24, 154);
    //Set the colour of the circle
    shape.setFillColor(Purple);

    sf::Clock clock;
    float deltaTime = 0.0f;


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
        shape.setPosition(position.x + 0.1, position.y + 0.1);

        //Render
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
