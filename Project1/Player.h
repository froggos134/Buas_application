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

class Player
{
private:
	


	
	Texture animation;

	
	int extraSpeedMax;
	
	int hpMax;

	int spritemovex;

	void initVariables();
	void initTextures();
	void initSprites();	
	

public:
	int extraSpeed;

	Sprite player_p;

	int hp;

	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();
	
	//accessors
	
	const Sprite& getTexture() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//functions
	void takeDamage(const int damage);
	void gainHealth(const int health);
	void gainSpeed(const int speed);
	void updateInput();
	//bool isAnyKeyPressed();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

