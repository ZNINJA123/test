#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class player
{
public:

	Texture standingTexture;
	Texture playerTexture;
	Texture jumpingTexture;
	Texture throwingTexture;
	Texture windmillTexture;
	Texture swordingTexture;
	Sprite playerSprite;
	IntRect standingRect[2];
	IntRect walkRect[3];
	IntRect swordRect[3];
	IntRect throwRect[2];
	IntRect jumpRect[4];
	IntRect windmillRect[3];
	int count;
	
	float animateTimer = 0.0f;
	Clock animateClock;

	bool running;
	bool standing;
	bool swordattack;
	bool facing;
	bool jumping;

	void input(Event e);
	float YVelocity;
	float XVelocity;
	float Gravity;

	player();
	player(Vector2f position, string texFileLoc, string runningFileLoc, string swordingFileLoc, string jumpingFileLoc, string throwingFileLoc, string windmillFileLoc);

	int animatePlayer(bool left = false);
	void update();

};