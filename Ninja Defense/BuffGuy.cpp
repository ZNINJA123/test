#include"BuffGuy.h"
#include<stdlib.h>
#include<iostream>
#include<SFML\System\Clock.hpp>
#include<stdlib.h>     
#include<time.h>

using std::cout;
using std::endl;
using namespace sf;

buffenemy::buffenemy() : buffenemy::buffenemy(Vector2f(255, 137), "Textures/BuffGuyWalking.png", "Textures/Dead.png")
{
}

buffenemy::buffenemy(Vector2f position, string buffFileloc, string deadFileLoc)
{
	buffTexture.loadFromFile(buffFileloc);
	deadTexture.loadFromFile(deadFileLoc);


	buffRect[0] = IntRect(0, 0, 14, 31);
	buffRect[1] = IntRect(16, 0, 14, 31);
	buffRect[2] = IntRect(32, 0, 13, 31);
	buffRect[3] = IntRect(47, 0, 15, 31);

	deadRect[0] = IntRect(0, 0, 31, 12);
	deadRect[1] = IntRect(33, 0, 20, 12);

	buffenemySprite.setScale(Vector2f(.7, .7));
	buffenemySprite.setOrigin(8, 12);
	buffenemySprite.setPosition(Vector2f(position.x, position.y));
	buffenemySprite.setTextureRect(buffRect[0]);
	buffenemySprite.setTexture(buffTexture);
	count = 0;

	bufff = true;
	dead = false;
	doneanimating = false;

}
int buffenemy::animatebuffguy(bool buff)
{
	if (buff)
	{
		buffenemySprite.setScale(.7f, .7f);
	}
	else
	{
		buffenemySprite.setScale(-.7f, .7f);
	}
	if (bufff)
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

void buffenemy::reset()
{
	bufff = true;
	dead = false;
	doneanimating = false;
	count = 0;
	buffenemySprite.setTextureRect(buffRect[0]);
	buffenemySprite.setTexture(buffTexture);
	buffenemySprite.setPosition(255, 137);
}

void buffenemy::update()
{
	buffenemy buffman;
	if (bufff)
	{
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 0.05f)
		{
			animatebuffguy();
			animateClock.restart();
		}
		buffenemySprite.setTexture(buffTexture);
		buffenemySprite.setTextureRect(buffRect[count]);
	}
	if (dead)
	{
		animateTimer = animateClock.getElapsedTime().asSeconds();
		if (animateTimer > 0.5f && !doneanimating)
		{
			animatebuffguy();
			animateTimer = 0;
			animateClock.restart();
		}
		else
		{
			animateTimer = animateClock.getElapsedTime().asSeconds();
			if (animateTimer > 1.0f && doneanimating)
			{
				dead = false;
				bufff = false;
				animateTimer = 0;
				animateClock.restart();
			}
		}
		bufff = false;
		buffenemySprite.setTexture(deadTexture);
		buffenemySprite.getPosition().x;
		buffenemySprite.setPosition(buffenemySprite.getPosition().x, 152);
		buffenemySprite.setTextureRect(deadRect[count]);
	}
	if (!dead && !bufff)
	{
		buffenemySprite.setPosition(999, 999);
	}
}