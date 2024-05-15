#include "Player.h"

void Player::initVariables()
{
	this->extraSpeed = 0;
	extraSpeedMax = 10;
	this->hpMax = 10;
	this->hp = hpMax;
	
	spritemovex = 0;
}


void Player::initTextures()
{
	
	animation.loadFromFile("Textures/AnimationSheet.png");

	if (!animation.loadFromFile("Textures/AnimationSheet.png"))
	{
		std::cout << " Could not load texture player" << "\n";
	}

	player_p.setTexture(animation);
	player_p.setTextureRect(IntRect(0, 24, 24, 24));
	player_p.setPosition(310, 220);
}
void Player::initSprites()
{
	
	player_p.scale(3.f, 3.f);
	
}


//constructor
Player::Player(float x, float y)
{
	//sets posiotion of player
	

	initVariables();
	initTextures();
	initSprites();
	

}

Player::~Player()
{
	
}

//accessors


const Sprite& Player::getTexture() const
{
	return player_p;
	// TODO: insert return statement here
}



const int& Player::getHp() const
{
	return this-> hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}


//functions

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}
	else if (this->hp < 0)
	{
		this->hp = 0;
	}


	
	if (extraSpeed > 0)
	{
		extraSpeed -= damage;
	}
	else if (extraSpeed < 0)
	{
		extraSpeed = 0;
	}



}

void Player::gainHealth(const int health)
{
	if (hp < hpMax)
	{

		hp += health;
	}

	if (hp > hpMax)
	{
		hp = hpMax;
	}

}


void Player::gainSpeed(const int speed)
{
	extraSpeed += speed;

	if (extraSpeed > 10)
	{
		extraSpeed = extraSpeedMax;
	}

	

	
}

void Player::updateInput()
{
	
	if (Keyboard::isKeyPressed(Keyboard::D))
	{

		spritemovex = (int)player_p.getPosition().x / 25 % 4; // devide by 4-> between 0/3, /10 for slower animation
		spritemovex = spritemovex * 24;
		player_p.setTextureRect(IntRect(spritemovex, 24, 24, 24));
		player_p.move(3+ extraSpeed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{

		spritemovex = (int)player_p.getPosition().x / 25 % 4; // devide by 4-> between 0/3, /10 for slower animation
		spritemovex = spritemovex * 24;
		player_p.setTextureRect(IntRect(spritemovex, 24, 24, 24));
		player_p.move(-3- extraSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{

		spritemovex = (int)player_p.getPosition().y / 25 % 4; // devide by 4-> between 0/3, /10 for slower animation
		spritemovex = spritemovex * 24;
		player_p.setTextureRect(IntRect(spritemovex, 24, 24, 24));
		player_p.move(0, 3 + extraSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{

		spritemovex = (int)player_p.getPosition().y / 25 % 4; // devide by 4-> between 0/3 for frames, /25 for slower animation
		spritemovex = spritemovex * 24;
		player_p.setTextureRect(IntRect(spritemovex, 24, 24, 24));
		player_p.move(0, -3 - extraSpeed);
	}

	

}

/*bool Player::isAnyKeyPressed()
{
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
		{
			
			//spritemovex = (int)player_p.getPosition().y / 25 % 4; // devide by 4-> between 0/3 for frames, /25 for slower animation
			spritemovex = 24 % 4;
			player_p.setTextureRect(IntRect(spritemovex, 0, 24, 24));
			
			
			return true; 
		}
			
	}
	return false;
}*/

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//left
	//recangle rectangle with four values: height,width,x,y

	if (this->player_p.getGlobalBounds().left <= 0.f)
		this->player_p.setPosition(0.f, this->player_p.getGlobalBounds().top);

	//not sf::FloatRect playerBounds = this-shape.get globalBounds(); because this only updates pos once
	//right collision
	if (this->player_p.getGlobalBounds().left + this->player_p.getGlobalBounds().width >= target->getSize().x)
		this->player_p.setPosition(target->getSize().x - this->player_p.getGlobalBounds().width, this->player_p.getGlobalBounds().top);

	//top
	if (this->player_p.getGlobalBounds().top <= 0.f)
		this->player_p.setPosition(this->player_p.getGlobalBounds().left, 0.f);

	//Botom collision
	if (this->player_p.getGlobalBounds().top + this->player_p.getGlobalBounds().height >= target->getSize().y)
		this->player_p.setPosition(this->player_p.getGlobalBounds().left, target->getSize().y - this->player_p.getGlobalBounds().height);
}


void Player::update(const sf::RenderTarget* target)
{
	/*window bounds collision
	//this->updateWindowBoundsCollision(target);--- not here because it wil go through and then update so it doest mmove padt window

	*/

	this->updateInput();
	//isAnyKeyPressed();

	//window bounds collision
	this->updateWindowBoundsCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->player_p);
}
