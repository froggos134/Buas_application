#pragma once



#include "Player.h"
#include "Swagball.h"
/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	VideoMode videoMode;
	RenderWindow* window;
	bool endGame;
	bool startGame;
	Event sfmlEvent;
    vector <SwagBall> swagBalls;
	Player player;
	Music city_of_backstreet;
	Music pitcher_perfect_theme;
	Music critical;

	Clock clock;

	int points;
	int colorBackground;
	int timerclock;


	Font font;
	Text guiText;
	Text endGameText;
	Text startGameText;

	
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;
	int playerHp;

	void initVariables();
	void initAudio();
	void initWindow();
	void initClock();
	
	void initFonts();
	void initText();
	


public:
	//constructors and destructors
	Game();
	~Game();

	//accessors, get variables from this class
	const bool& getEndGame() const;
	const bool& getStartGame() const;

	//modifiers, modify variables in this class

	//functions, all kinds of stuff

	const bool running() const;
	void pollEvents();

	void spawnSwagBalls();
	const int randBallType() const ;
	void updatePlayer();
	
	void updateCollision();
	void updateGui();
	void updateGameStatus();
	void update();

	void renderGui(RenderTarget* target);
	void render();

};