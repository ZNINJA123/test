#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class enemy
{
public:
	Texture baseballTexture;
	Texture deadTexture;

	Sprite enemySprite;

	IntRect baseballRect[3];
	IntRect deadRect[2];

	float animateTimer = 0.0f;
	Clock animateClock;

	bool base;
	bool dead;
	bool doneanimating;

	int count;
	int animateEnemy(bool man = false);

	enemy();
	enemy(Vector2f position, string baseballFileLoc, string deadFileLoc);
	
	void reset();
	void update();
};