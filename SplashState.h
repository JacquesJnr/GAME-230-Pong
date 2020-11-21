#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameMaster.h"

namespace Pong 
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		void Init();

		void handleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _image;
	};
}



