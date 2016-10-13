#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class buffenemy
{
public:
	Texture buffTexture;
	Texture deadTexture;
	Texture buffattackTexture;

	Sprite buffenemySprite;

	IntRect buffRect[4];
	IntRect deadRect[2];
	IntRect buffattackRect[2];

	float animateTimer = 0.0f;
	Clock animateClock;

	bool bufff;
	bool dead;
	bool buffattack;
	bool doneanimating;

	int count;
	int animatebuffguy(bool buff = false);

	buffenemy();
	buffenemy(Vector2f position, string buffFileloc, string deadFileLoc);

	void reset();
	void update();




};