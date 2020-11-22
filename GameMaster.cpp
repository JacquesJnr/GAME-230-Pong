#include "GameMaster.h"
#include "SplashState.h"

namespace Pong 
{
	GameMaster::GameMaster(int width, int height, string title)
	{
		_gameData->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		//_gameData->theMachine.AddState();


		this->Run();
	}

	void GameMaster::Run()
	{
		float newTime, frameTime, interp;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_gameData->window.isOpen()) {
			this->_gameData->theMachine.ProcessStateChanges();
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= deltaTime) {
				this->_gameData->theMachine.GetActiveState()->HandleInput();
				this->_gameData->theMachine.GetActiveState()->Update(deltaTime);

				accumulator -= deltaTime;
			}

			interp = accumulator / deltaTime;
			this->_gameData->theMachine.GetActiveState()->Draw(interp);
		}
	}

}