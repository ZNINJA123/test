#include"Player.h"
#include<stdlib.h>
#include<iostream>
#include<SFML\System\Clock.hpp>
#include<time.h>

using std::cout;
using std::endl;
using namespace sf;
void player::input(Event e)
{
	if (e.key.code == Keyboard::Up && jumping == false)
	{
		YVelocity = 2;
		jumping = true;
	}
}
player::player() : player::player(Vector2f(120, 140), "Textures/ninjastanding.png", "Textures/ninjarunning.png", "Textures/ninjaswordattack.png", "Textures/NinjaThrowing.png", "Textures/ninjajumping.png", "Textures/NinjaWindmill.png")
{
}

player::player(Vector2f position, string texFileLoc, string runningFileLoc, string swordingFileloc, string throwingFileLoc, string jumpingFileLoc, string windmillFileLoc)
{

	standingTexture.loadFromFile(texFileLoc);
	playerTexture.loadFromFile(runningFileLoc);
	swordingTexture.loadFromFile(swordingFileloc);
	jumpingTexture.loadFromFile(jumpingFileLoc);
	throwingTexture.loadFromFile(throwingFileLoc);
	windmillTexture.loadFromFile(windmillFileLoc);

	standingRect[0] = IntRect(0, 0, 16, 31);
	standingRect[1] = IntRect(17, 0, 16, 31);

	walkRect[0] = IntRect(0, 0, 21, 30);
	walkRect[1] = IntRect(22, 0, 20, 30);
	walkRect[2] = IntRect(42, 0, 19, 30);

	swordRect[0] = IntRect(0, 0, 16, 30);
	swordRect[1] = IntRect(18, 0, 35, 30);
	swordRect[2] = IntRect(54, 0, 31, 30);

	jumpRect[0] = IntRect(0, 0, 19, 24);
	jumpRect[1] = IntRect(21, 0, 15, 24);
	jumpRect[2] = IntRect(38, 0, 19, 24);
	jumpRect[3] = IntRect(59, 0, 15, 24);

	running = false;
	standing = false;
	swordattack = false;
	facing = false;
	jumping = false;
	playerSprite.setScale(Vector2f(.7, .7));
	playerSprite.setOrigin(7.5, 15.5);
	playerSprite.setPosition(position.x, position.y);
	playerSprite.setTextureRect(standingRect[0]);
	playerSprite.setTexture(standingTexture);
	count = 0;
	YVelocity = 0;
	XVelocity = 0;
	Gravity = 1;
}

int player::animatePlayer(bool left)
{
	if (left)
	{
		playerSprite.setScale(-.7f, .7f);
	}
	else
	{
		playerSprite.setScale(.7f, .7f);
	}
	if (running)
	{
		if (count < 2)
		{
			count++;
		}
		else
		{
			count = 0;
		}
	}
	if (standing)
	{
		if (count < 1)
		{
			count++;
		}
		else
		{
			count = 0;
		}

	}
	if (swordattack)
	{
		if (count < 2)
		{
			count++;
		}
		else
		{
			swordattack = false;
			count = 0;
			animatePlayer(facing);
		}
	}
	if (jumping)
	{
		if (count < 3)
		{
			count++;
		}
		else
		{
			count = 0;
		}
	}
	return count;
}

void player::update()
{
	//cout << "running " << running << endl;
	//cout << "standing " << standing << endl;
	if (jumping)
	{
		YVelocity -= Gravity*0.06f;
		if (YVelocity != 0)
		{
			if (facing == false)
			{
				playerSprite.move(XVelocity + (.2), -YVelocity);

			}
			else
			{
				playerSprite.move(XVelocity - (.2), -YVelocity);

			}
		}
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 0.19f)
		{
			animatePlayer(facing);
			animateTimer = 0;
			animateClock.restart();
		}
		standing = false;
		running = false;
		swordattack = false;
		playerSprite.setTexture(jumpingTexture);
		playerSprite.setTextureRect(jumpRect[count]);
	}
	if (standing)
	{
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 0.2f)
		{
			animatePlayer(facing);
			animateTimer = 0;
			animateClock.restart();
		}
		jumping = false;
		running = false;
		swordattack = false;
		playerSprite.setTexture(standingTexture);
		playerSprite.setTextureRect(standingRect[count]);
	}
	if (running)
	{
		playerSprite.setTexture(playerTexture);
		swordattack = false;
		standing = false;
		playerSprite.setTextureRect(walkRect[count]);

	}
	if (swordattack)
	{
		playerSprite.setTextureRect(swordRect[count]);
		playerSprite.setTexture(swordingTexture);
		standing = false;
		running = false;

	}
}