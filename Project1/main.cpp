#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{
	//game loop initialize random seed, needed for randomization
	srand(static_cast<unsigned>(time(0)));


	//initialize game object
	Game game;
	//std::vector <SwagBall> swagBalls;

	//Game loop
	while (game.running())
	{
		
		game.update();
		game.render();
	
	}

	//End of application
	return 0;
}