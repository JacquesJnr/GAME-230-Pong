#pragma once
#include <SFML/Graphics.hpp>

namespace Pong {
	
	class InputManager
	{
	public:

		InputManager() {}
		~InputManager() {}

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};

}


