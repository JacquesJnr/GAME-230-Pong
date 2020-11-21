#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "State.h"
using namespace std;

namespace Pong 
{
	struct Game
	{
		StateMachine theMachine;
		sf::RenderWindow window;
		AssetManager asstes;
		InputManager input;
	};

	typedef shared_ptr<Game> GameDataRef;

	class GameMaster {
	public:
		GameMaster(int width, int height, string title);

	private:
		const float deltaTime = 1.0 / 60.0f;
		sf::Clock _clock;
		GameDataRef  _gameData = make_shared<Game>();

		void Run( );
	};
}

