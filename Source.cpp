#include <cmath>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include "Collider.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameMaster.h"
using namespace std;
using namespace Pong;

#define WIDTH 1024;
#define HEIGHT 768;

int main()
{
	Pong::Game(1024, 768, "SFML");

	return EXIT_SUCCESS;
}

