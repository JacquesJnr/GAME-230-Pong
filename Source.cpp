#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "GAME 230 - Pong");

    sf::Font font;
    if (!font.loadFromFile("data/Fonts/OpenSans-Regular.ttf")) {
        return 1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Pong!");
    title.setCharacterSize(42);
    title.setFillColor(sf::Color::Red);
    //title.setStyle(sf::Text::Regular);
    title.setPosition(400, 20);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("data/Sounds/sound.ogg")) {
        return 1;
   }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    sf::Texture iconTexture;
    if (!iconTexture.loadFromFile("data/Textures/UnityIcon.png"))
    {
        return 1;
    }

    iconTexture.setSmooth(true);
    sf::Sprite icon;
    icon.setTexture(iconTexture);
    icon.setScale(0.5f, 0.5f);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        //window.draw(title);
        //window.draw(icon);
        window.display();
    }

    return 0;
}
