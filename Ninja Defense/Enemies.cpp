#include"Enemies.h"
#include<stdlib.h>
#include<iostream>
#include<SFML\System\Clock.hpp>
#include<stdlib.h>     
#include<time.h>

using std::cout;
using std::endl;
using namespace sf;

enemy::enemy() : enemy::enemy(Vector2f(0, 138), "Textures/BaseballEnemy.png", "Textures/Dead.png")
{
}
enemy::enemy(Vector2f position, string baseballFileLoc, string deadFileLoc)
{
	baseballTexture.loadFromFile(baseballFileLoc);
	deadTexture.loadFromFile(deadFileLoc);
	srand(time(0));

	baseballRect[0] = IntRect(0, 0, 14, 39);
	baseballRect[1] = IntRect(16, 0, 22, 39);
	baseballRect[2] = IntRect(40, 0, 23, 39);

	deadRect[0] = IntRect(0, 0, 31, 12);
	deadRect[1] = IntRect(33, 0, 20, 12);
	base = true;
	dead = false;
	doneanimating = false;
	
	enemySprite.setScale(Vector2f(.7, .7));
	enemySprite.setOrigin(7., 19.5);
	enemySprite.setPosition(Vector2f(position.x, position.y));
	enemySprite.setTextureRect(baseballRect[0]);
	enemySprite.setTexture(baseballTexture);
	count = 0;

}
int enemy::animateEnemy(bool man)
{
	if (man)
	{
		enemySprite.setScale(-.7f, .7f);
	}
	else
	{
		enemySprite.setScale(.7f, .7f);
	}
	if (base)
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
	if (dead)
	{
		if (count < 1)
		{
			count++;
		}
		else
		{
			count = 0;
			doneanimating = true;
		}
	}
	return count;
}

void enemy::reset()
{
	base = true;
	dead = false;
	doneanimating = false;
	count = 0;
	enemySprite.setTextureRect(baseballRect[0]);
	enemySprite.setTexture(baseballTexture);
}

void enemy::update()
{
	enemy baseball;
	if (base)
	{
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 0.05f)
		{
			animateEnemy();
			animateTimer = 0;
			animateClock.restart();
		}
		enemySprite.setTexture(baseballTexture);
		enemySprite.setTextureRect(baseballRect[count]);
	}
	if (dead)
	{
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 1.0f && !doneanimating)
		{
			animateEnemy();
			animateTimer = 0;
			animateClock.restart();
		}
		else 
		{
			animateTimer = animateClock.getElapsedTime().asSeconds();
			if (animateTimer > 1.5f && doneanimating)
			{
				dead = false;
				base = false;
				animateClock.restart();
			}
		}
		base = false;
		enemySprite.setTexture(deadTexture);
		enemySprite.getPosition().x;
		enemySprite.setPosition(enemySprite.getPosition().x, 157);
		enemySprite.setTextureRect(deadRect[count]);
	}
	if (!dead && !base)
	{
		enemySprite.setPosition(999, 999);
	}
}