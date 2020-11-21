#include "SplashState.h"
#include "Definitions.h"
#include <sstream>
#include <iostream>

namespace Pong
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}
	
	void SplashState::Init()
	{
		this->_data->asstes.LoadTexture("bg", SPLASH_IMAGE_FILE_PATH);
		
		_image.setTexture(this->_data->asstes.GetTexture("bg") );

	}
	void SplashState::handleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent (event))
		{
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
		}
	}
	void SplashState::Update(float deltaTime)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) 
		{
			 //Switch to the Game
		}
	}
	void SplashState::Draw(float deltaTime)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_image);

		this->_data->window.display();
	}
}