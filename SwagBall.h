#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include <ctime>

using namespace std;
using namespace sf;

enum SwagBallTypes{DEFAULT = 0, DAMAGING, HEALING, SPEED, NROFTYPES};

class SwagBall
{
private:
	sf::CircleShape shape;
	int type;


	void initShape(const sf::RenderWindow& window);

public:
	SwagBall(const sf::RenderWindow& window, int type);
	virtual ~SwagBall();

	//accessor
	 sf::CircleShape  getShape() ;
	 void updateMove();
	const int& getType()const;

	//functions
	void update();
	void render(sf::RenderTarget&target);
};

