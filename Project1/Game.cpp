#include "Game.h"


void Game::initVariables()
{
	endGame = false;
	startGame = false;
	spawnTimerMax = 10.f;
	spawnTimer = spawnTimerMax;
	maxSwagBalls = 15;
	points = 0;
	colorBackground = points;
	
	
}

void Game::initAudio()
{
	city_of_backstreet.openFromFile("Audio/City_of_Backstreet.ogg");

	if (!city_of_backstreet.openFromFile("Audio/City_of_Backstreet.ogg"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD Audio/City of Backstreet.ogg" << "\n";
	}

	city_of_backstreet.play();
	
	pitcher_perfect_theme.openFromFile("Audio/PitcherPerfectTheme.wav");

	if (!pitcher_perfect_theme.openFromFile("Audio/PitcherPerfectTheme.wav"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD Audio/PitcherPerfectTheme.wav" << "\n";
	}

	
}

void Game::initWindow()
{
	videoMode = VideoMode(800, 600);
	window = new RenderWindow(this->videoMode, "BUAS Apllication Game", Style::Close | Style::Titlebar);
	window->setFramerateLimit(60);


}

void Game::initClock()
{

	if (clock.getElapsedTime().asSeconds() > 60)
	{
		endGame = true;
		
	}
}



void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD Dosis - Light.ttf" << "\n";
	}
	
}

void Game::initText()
{
	//gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);

	//endgame text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	endGameText.setPosition(sf::Vector2f(115, 100));
	
	startGameText.setFont(font);
	startGameText.setFillColor(Color::Blue);
	startGameText.setCharacterSize(33);
	startGameText.setPosition(Vector2f(40, 50));
}

//Private functions
//constructors and destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	initAudio();
	
}

Game::~Game()
{
	delete this->window;

}

const bool& Game::getEndGame() const
{
	return endGame;
}

const bool& Game::getStartGame() const
{
	return startGame;
}

//functions
const bool Game::running() const
{
	//whille window is running-> main and while end game is false
	return this->window->isOpen() /* && endGame == false*/;
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this-> sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}

	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	
	else
	{
		if(this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window,this->randBallType()));

			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand()%100+1;

	if (randValue > 45 && randValue <= 68)
		type = SwagBallTypes::SPEED;
	else if(randValue >68 && randValue<=85)
		type=SwagBallTypes::DAMAGING;
	else if (randValue > 85 && randValue  <=100)
		type = SwagBallTypes::HEALING;
	

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}





void Game::updateCollision()
{
	//check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getTexture().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			/*how you erase an element form a vector using an iterator
				-begin is first element
				-i is how many iterations have been done in the for loop
			
			*/

			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				
				break;
				
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				
				break;

			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;

			case SwagBallTypes::SPEED:
				player.gainSpeed(1);

				break;
			}

		

			//remove the balls
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateGui()
{
	stringstream gui;


	gui << "- Points: "<<this->points<<"\n"
		<< "- Health" << player.hp <<"/"<<player.getHpMax() << "\n"
		<< "- Time: "<< clock.getElapsedTime().asSeconds() << "\n";

	this->guiText.setString(gui.str());

	stringstream endg;

	endg << "               Time's Up!" << "\n"
		<< "      You scored: "<< points << "  Points!" << "\n"
		<< "               Good Job!" << "\n" << "\n"
		<< "Press Enter to go to credits" << "\n";

	endGameText.setString(endg.str());

	stringstream startg;

	startg << "Thank you for playing my BUAS Application game!" << "\n"
		<< "Assets used in this game:" << "\n"
		<< " - NOT JAM MUSIC: TRACK No.4 Pitcher Perfect " << "\n"
		<< "     by Not Jam " << "\n"
		<< " - Swngyill's Retro Music Pack - Vol. 001 : City of Backstreet" << "\n"
		<< "     by Swngyill YOON " << "\n"
		<< " - Pixel Protagonist" << "\n"
		<< "     by Penzilla " << "\n"
		<< "                ---All assets were aquired from Itchi.io---" << "\n" << "\n"

		<< "                        Press Escape to close the game." << "\n"
			<< "                          Or... press Space to play again!" << "\n";
		 

	startGameText.setString(startg.str());
}

void Game::updateGameStatus()
{

	if (startGame == true)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			endGame = false;
			startGame = false;
			clock.restart();
			points = 0;
			player.player_p.setPosition(310, 220);
			player.hp = 10;
			pitcher_perfect_theme.stop();
			city_of_backstreet.play();
			
		}
		
	}

	if (endGame == true)
	{
		city_of_backstreet.stop();
		
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			endGame = false;
			startGame = true;
			pitcher_perfect_theme.play();
		}
	}
	
	
	
}

void Game::update()
{
	this->pollEvents();

	if (endGame == false && startGame==false)
	{
	this->spawnSwagBalls();
	this->updatePlayer();
	//^^makes sure that the player cpp/player.h are functional (on the screen)
	
	this->updateCollision();
	this->updateGui();
	initClock();
	}
	
	
	updateGameStatus();
	

}

void Game::renderGui(sf::RenderTarget*target)
{
	target->draw(this->guiText);
}

void Game::render()
{

	if(endGame == false&& startGame==false)
	{
		colorBackground = 2*points;
		this->window->clear(Color(0, colorBackground, colorBackground));
	
	}
	

	//render stuff

	this->player.render(this->window);

	//^^makes sure that the player cpp/player.h are drawn onto the screen

	for (auto i : this->swagBalls)
	{
		i.render(*this->window);
	}

	//render gui
	this->renderGui(this->window);

	//render endgame
	if (startGame == true)
	{
		window->clear(Color(0, 255, 255));
		window->draw(startGameText);
		
	}

	if (endGame == true)
	{

		window->clear(Color(40, 0, 0));
		window->draw(endGameText);
		
	}
	



	this->window->display();
}


