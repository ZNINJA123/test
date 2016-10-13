#include <stdlib.h>
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Clock.hpp>
#include "Player.h"
#include "Enemies.h"
#include "BuffGuy.h"
#include <vector>
#include <time.h>
#include "Music.h"
#include "highscore.h"
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(900, 600), "Ninja Defense");
	Texture background;
	Texture mmbackground;
	Texture GObackground;
	Sprite goSprite;
	Sprite mmSprite;
	Sprite bgSprite;
	Clock animateClock;
	player ninja;
	Text playertext;
	Text initials;
	Text restart;
	Sprite floor;
	std::string str;
	Texture floortexture;
	highscore table;
	string highscores[5];
	string initial[5];
	Text hs[5];
	table.readhighscore(highscores, initial, 5);

	CMusic musicplayer = CMusic::Getinstance();
	int enemydeath;
	int enemydeath2;
	int swordhit;
	int score100;
	int swordsound;
	int playerdeath;
	int mainMenuBGM;
	int levelBGM;
	int gameoverbg;
	enemydeath = musicplayer.CreateSFX("enemydeath.wav");
	enemydeath2 = musicplayer.CreateSFX("enemydeath2.wav");
	swordhit = musicplayer.CreateSFX("swordhit.wav");
	score100 = musicplayer.CreateSFX("powerup.wav");
	swordsound = musicplayer.CreateSFX("swordsound.wav");
	playerdeath = musicplayer.CreateSFX("deathsoundplayer.wav");
	mainMenuBGM = musicplayer.CreateMusic("mmbgm.wav");
	levelBGM = musicplayer.CreateMusic("09 Evading the Enemy [Stages 2-1 & 6-1].wav");
	gameoverbg = musicplayer.CreateMusic("backgroundsound.wav");

	bool gameover = false;
	bool keyheld = false;
	bool mainmenu = true;

	enemy baseball[50];
	buffenemy buffguy[50];
	vector<buffenemy> alive;
	vector<buffenemy> dead;
	vector<enemy> liveEnemies;
	vector<enemy> deadEnemies;
	srand(time(0));



	int health = 100;
	int score = 0;
	Text scoreText;
	Text healthText;
	Text highscoreText;
	Font gameFont;
	gameFont.loadFromFile("Font/comicbd.ttf");

	healthText.setFont(gameFont);
	healthText.setString("  Health:" + to_string(health));
	healthText.setCharacterSize(14);
	healthText.setColor(Color::Red);
	healthText.setPosition(Vector2f(3, 0));

	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + to_string(score));
	scoreText.setCharacterSize(14);
	scoreText.setColor(Color::Green);
	scoreText.setPosition(Vector2f(15, 12));

	float animateTimer = 0.0f;
	background.loadFromFile("Textures/bossroom.png");
	floortexture.loadFromFile("Textures/floor.png");
	mmbackground.loadFromFile("Textures/2.png");
	GObackground.loadFromFile("Textures/1.png");
	goSprite.setTexture(GObackground);
	mmSprite.setTexture(mmbackground);
	floor.setTexture(floortexture);
	bgSprite.setTexture(background);
	//background.setSmooth(true);
	//ninja.playerTexture.setSmooth(true);
	//ninja.standingTexture.setSmooth(true);
	//ninja.swordingTexture.setSmooth(true);
	//baseball.baseballTexture.setSmooth(true);
	//baseball.deadTexture.setSmooth(true);
	floor.setPosition(0, 152);
	window.setFramerateLimit(60);
	window.setSize(Vector2u(900, 600));
	window.setPosition(Vector2i(0, 0));
	View view(Vector2f(128, 88), Vector2f(224, 175));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);
	bool playonce = false;
	bool scoreonce = true;
	Clock baseballspawnclock;
	float baseballspawntimer;

	Clock buffguyspawnclock;
	float buffguyspawntimer;
	while (window.isOpen())
	{
		Text subtext;
		
		
		subtext.setFont(gameFont);
		subtext.setCharacterSize(12);
		subtext.setPosition(60, 112);
		subtext.setString("Press Enter to Play");
		subtext.setColor(Color::White);
		scoreText.setString("NINJA DEFENSE");
		scoreText.setColor(Color::Red);
		scoreText.setCharacterSize(20);
		scoreText.setPosition(40, 92);
		playertext.setFont(gameFont);
		playertext.setCharacterSize(10);
		playertext.setPosition(135, 6);
		playertext.setColor(Color::White);
		initials.setFont(gameFont);
		initials.setString("Enter your Initials:");
		initials.setColor(Color::Magenta);
		initials.setCharacterSize(10);
		initials.setPosition(20, 6);
		if (mainmenu == true)
		{
			Event e;

		
			if (playonce == false)
			{
				musicplayer.PlayMusic(mainMenuBGM);
				playonce = true;
			}
			while (window.pollEvent(e))
			{
				if (e.type == Event::TextEntered)
				{
					if (e.text.unicode < 128 && str.length() < 3)
					{
						str += static_cast<char>(e.text.unicode);
						playertext.setString(str);
					}
				}
				if (e.type == Event::Closed)
					window.close();
				if (e.type == Event::KeyPressed)
				{

					if (e.key.code == Keyboard::Return)
					{
						musicplayer.StopMusic(mainMenuBGM);
						playonce = false;
						mainmenu = false;
					}
				}
			}
			ninja.standing = true;
			ninja.update();
			window.clear();
			window.draw(mmSprite);
			window.draw(ninja.playerSprite);
			window.draw(scoreText);
			window.draw(subtext);
			window.draw(playertext);
			window.draw(initials);
			window.display();

		}
		 if (!gameover && !mainmenu)
		{
			 if (playertext.getString().getSize() < 2)
			 {
				 playertext.setString("JTR");
			 }
			 baseballspawntimer = baseballspawnclock.getElapsedTime().asSeconds();
			 if (baseballspawntimer > 2.0f)
			 {
				 enemy *base = new enemy();
				 liveEnemies.push_back(*base);
				 baseballspawnclock.restart();
			 }
			buffguyspawntimer = buffguyspawnclock.getElapsedTime().asSeconds();
			 if (buffguyspawntimer > 3.5f)
			 {
				 buffenemy *buff = new buffenemy();
				 alive.push_back(*buff);
				 buffguyspawnclock.restart();
			 }
			 if (playonce == false)
			 {
				 musicplayer.PlayMusic(levelBGM);
				 playonce = true;
			 }
			 scoreText.setString("Score: " + to_string(score));
			 scoreText.setCharacterSize(14);
			 scoreText.setColor(Color::Green);
			 scoreText.setPosition(Vector2f(15, 12));
		Event e;
		while (window.pollEvent(e))
		{
			window.clear();
		//	window.setView(view);
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
			{
				ninja.input(e);
				if (e.key.code == Keyboard::Z&&ninja.swordattack == false)
				{
					musicplayer.PlaySFX(swordsound);
					ninja.standing = false;
					ninja.running = false;
					ninja.swordattack = true;
					animateTimer = animateClock.getElapsedTime().asSeconds();
					if (animateTimer > 0.06f)
					{
						ninja.animatePlayer(ninja.facing);
						animateClock.restart();

					}
				}
				if (e.key.code == Keyboard::Left&&ninja.swordattack == false)
				{
					ninja.facing = true;
					ninja.standing = false;
					ninja.swordattack = false;
					ninja.running = true;
					if (ninja.playerSprite.getPosition().x > 26)
					{
						ninja.playerSprite.move(-2, -ninja.YVelocity);
						ninja.XVelocity = -.2;
					}
					if (view.getCenter().x - (view.getSize().x*0.5f) > 0)
					{

						view.move(-.8, 0);

					}
					animateTimer = animateClock.getElapsedTime().asSeconds();
					if (animateTimer > 0.08f)
					{
						ninja.animatePlayer(ninja.facing);
						animateClock.restart();

					}
				}
				if (e.key.code == Keyboard::Right&&ninja.swordattack == false)
				{
					ninja.facing = false;
					ninja.standing = false;
					ninja.swordattack = false;
					ninja.running = true;
					if (ninja.playerSprite.getPosition().x != 220)
					{
						ninja.playerSprite.move(2, -ninja.YVelocity);
						ninja.XVelocity = .2;
					}
					if (view.getCenter().x + (view.getSize().x*0.5f) < 250)
					{
						view.move(.8, 0);

					}
					animateTimer = animateClock.getElapsedTime().asSeconds();
					if (animateTimer > 0.08f)
					{
						ninja.animatePlayer(ninja.facing);
						animateClock.restart();

					}
				}

			}
			else
			{
				if (ninja.swordattack == false)
				{
					ninja.standing = true;
					ninja.running = false;
					ninja.swordattack = false;
				}
			}
		}
		if (ninja.playerSprite.getGlobalBounds().intersects(floor.getGlobalBounds()))
		{
			ninja.jumping = false;
			ninja.standing = true;
			ninja.playerSprite.setPosition(ninja.playerSprite.getPosition().x, 140);
			ninja.YVelocity = 0;
		}
#pragma region swordattack
		if (ninja.swordattack)
		{
			animateTimer = animateClock.getElapsedTime().asSeconds();
			if (animateTimer > 0.08f)
			{
				ninja.animatePlayer(ninja.facing);
				animateClock.restart();

			}
			for (int p = 0; p < alive.size(); p++)
			{
				if (ninja.playerSprite.getGlobalBounds().intersects(alive[p].buffenemySprite.getGlobalBounds()) && ninja.swordattack == true && ninja.facing != true)
				{
					alive[p].dead = true;
					musicplayer.PlaySFX(enemydeath);
					musicplayer.PlaySFX(swordhit);
					score = score + 10;
					scoreText.setString("Score: " + to_string(score));
					dead.push_back(alive[p]);
					alive.erase(alive.begin() + p);
				}
			}
			for (int i = 0; i < liveEnemies.size(); i++)
			{
				if (ninja.playerSprite.getGlobalBounds().intersects(liveEnemies[i].enemySprite.getGlobalBounds()) && ninja.swordattack == true && ninja.facing != false)
				{
					liveEnemies[i].dead = true;
					musicplayer.PlaySFX(enemydeath2);
					musicplayer.PlaySFX(swordhit);
					score = score + 10;
					scoreText.setString("Score: " + to_string(score));
					deadEnemies.push_back(liveEnemies[i]);
					liveEnemies.erase(liveEnemies.begin() + i);
				}
			}
			if (score % 100 == 0)
			{
				musicplayer.PlaySFX(score100);
			}
			else
			{
				musicplayer.StopSFX(score100);
			}
			ninja.update();
		}
#pragma endregion
#pragma region buffguyupdate
		for (int p = 0; p < alive.size(); p++)
		{
			if (alive[p].buffenemySprite.getGlobalBounds().intersects(ninja.playerSprite.getGlobalBounds()) && alive[p].dead == false && alive[p].bufff == true)
			{
				animateTimer = animateClock.getElapsedTime().asMilliseconds();
				if (animateTimer > 199.0f)
				{
					health = health - 20;
					healthText.setString("  Health:" + to_string(health));
					animateClock.restart();
				}
				ninja.update();
			}
			if (alive[p].buffenemySprite.getPosition().x != -5)
			{
				alive[p].buffenemySprite.move(-.5, 0);
				if (alive[p].dead == true)
				{
					alive[p].buffenemySprite.move(.5, 0);
				}
			}
			if (alive[p].dead == false && alive[p].buffenemySprite.getPosition().x <= 0)
			{
				alive[p].buffenemySprite.setPosition(255, 137);
			}
			alive[p].update();
		}
		if (dead.size() > alive.size())
		{
			for (int p = 0; p < dead.size(); p++)
			{
				if (dead[p].dead == false && dead[p].bufff == false)
				{
					dead[p].reset();
					alive.push_back(dead[p]);
					dead.clear();
				}

			}
		}
		for (int p = 0; p < dead.size(); p++)
		{
			dead[p].update();
		}
		ninja.update();
#pragma endregion
#pragma region baseballupdate

		for (int i = 0; i < liveEnemies.size(); i++)
		{
			if (liveEnemies[i].enemySprite.getGlobalBounds().intersects(ninja.playerSprite.getGlobalBounds()) && liveEnemies[i].dead == false && liveEnemies[i].base == true)
			{
				animateTimer = animateClock.getElapsedTime().asMilliseconds();
				if (animateTimer > 199.0f)
				{
					health = health - 10;
					healthText.setString("  Health:" + to_string(health));
					animateClock.restart();
				}
				ninja.update();
			}

			if (liveEnemies[i].enemySprite.getPosition().x != 256)
			{
				liveEnemies[i].enemySprite.move(.5, 0);
				if (liveEnemies[i].dead == true)
				{
					liveEnemies[i].enemySprite.move(-.5, 0);
				}
			}
			if (liveEnemies[i].dead == false && liveEnemies[i].enemySprite.getPosition().x > 255)
			{
				liveEnemies[i].enemySprite.setPosition(0, 138);
			}
			liveEnemies[i].update();


		}
		if (deadEnemies.size() > liveEnemies.size())
		{
			for (int i = 0; i < deadEnemies.size(); i++)
			{
				if (deadEnemies[i].dead == false && deadEnemies[i].base == false)
				{
					deadEnemies[i].reset();
					liveEnemies.push_back(deadEnemies[i]);
					deadEnemies.clear();
				}

			}
		}
		for (int i = 0; i < deadEnemies.size(); i++)
		{
			deadEnemies[i].update();
		}
#pragma endregion 
		window.clear();
			window.draw(bgSprite);
			window.draw(ninja.playerSprite);
			window.draw(healthText);
			window.draw(scoreText);
			window.draw(floor);
			for (int p = 0; p < alive.size(); p++)
			{
				window.draw(alive[p].buffenemySprite);
			}
			for (int p = 0; p < dead.size(); p++)
			{
				window.draw(dead[p].buffenemySprite);
			}
			for (int i = 0; i < liveEnemies.size(); i++)
			{
				window.draw(liveEnemies[i].enemySprite);
			}
			for (int i = 0; i < deadEnemies.size(); i++)
			{
				window.draw(deadEnemies[i].enemySprite);
			}
			if (health <= 0)
			{
				gameover = true;
				playonce = false;
				musicplayer.StopMusic(levelBGM);
				musicplayer.PlaySFX(playerdeath);
				if (playonce == false)
				{
					musicplayer.PlayMusic(gameoverbg);
					playonce = true;
				}
			}
			window.display();

		}
		else if (gameover == true && mainmenu == false)
		{
			Event e;
			view.setSize(Vector2f(210, 210));
			window.setView(view);
			if (scoreonce)
			{
				if (score > atoi(highscores[0].c_str()))
				{
					highscores[4] = highscores[3];
					initial[4] = initial[3];

					highscores[3] = highscores[2];
					initial[3] = initial[2];

					highscores[2] = highscores[1];
					initial[2] = initial[1];

					highscores[1] = highscores[0];
					initial[1] = initial[0];

					std::stringstream ss;
					ss << score;

					highscores[0] = ss.str();
					initial[0] = playertext.getString();
				}
				else if (score > atoi(highscores[1].c_str()))
				{
					highscores[4] = highscores[3];
					initial[4] = initial[3];

					highscores[3] = highscores[2];
					initial[3] = initial[2];

					highscores[2] = highscores[1];
					initial[2] = initial[1];

					std::stringstream ss;
					ss << score;

					highscores[1] = ss.str();
					initial[1] = playertext.getString();
				}
				else if (score > atoi(highscores[2].c_str()))
				{
					highscores[4] = highscores[3];
					initial[4] = initial[3];

					highscores[3] = highscores[2];
					initial[3] = initial[2];

					std::stringstream ss;
					ss << score;

					highscores[2] = ss.str();
					initial[2] = playertext.getString();
				}
				else if (score > atoi(highscores[3].c_str()))
				{
					highscores[4] = highscores[3];
					initial[4] = initial[3];

					std::stringstream ss;
					ss << score;

					highscores[3] = ss.str();
					initial[3] = playertext.getString();
				}
				else if (score > atoi(highscores[4].c_str()))
				{
					std::stringstream ss;
					ss << score;

					highscores[4] = ss.str();
					initial[4] = playertext.getString();
				}
				scoreonce = false;
			}
		

			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
					window.close();
				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::R)
					{
						liveEnemies.clear();
						alive.clear();
						deadEnemies.clear();
						dead.clear();
						scoreonce = true;
						health = 100;
						score = 0;
						ninja.facing = !true;
						gameover = false;
						playonce = false;
						mainmenu = true;
						ninja.jumping = false;
						musicplayer.StopMusic(gameoverbg);
						View view2(Vector2f(128, 88), Vector2f(224, 175));
						view2.setViewport(FloatRect(0, 0, 1, 1));
						window.setView(view2);
						playertext.setString("");
						str.clear();
						ninja.playerSprite.setPosition(120, 140);
						//alive[0].buffenemySprite.setPosition(255, 138);
						//liveEnemies[0].enemySprite.setPosition(0, 138);
						view.setCenter(Vector2f(128, 88));
						scoreText.setString("Score: " + to_string(score));
						scoreText.setCharacterSize(14);
						scoreText.setColor(Color::Green);
						scoreText.setPosition(Vector2f(15, 12));

						healthText.setFont(gameFont);
						healthText.setString("  Health:" + to_string(health));
						healthText.setCharacterSize(14);
						healthText.setColor(Color::Red);
						healthText.setPosition(Vector2f(3, 0));
					}
				}
			}
			if (gameover == true)
			{
				restart.setFont(gameFont);
				restart.setString("Press R to Play Again");
				restart.setCharacterSize(8);
				restart.setColor(Color::Red);
				restart.setPosition(80, 8);

				healthText.setString("Game Over");
				healthText.setColor(Color::Magenta);
				healthText.setCharacterSize(20);
				healthText.setPosition(72, -16);

				highscoreText.setFont(gameFont);
				highscoreText.setString("HighScores");
				highscoreText.setCharacterSize(16);
				highscoreText.setColor(Color::Yellow);
				highscoreText.setPosition(78, 22);

				for (int i = 0; i < 5; i++)
				{
					hs[i].setFont(gameFont);
					hs[i].setString(initial[i] + " " + highscores[i]);
					hs[i].setPosition(90, 48 + (i * 20));
					hs[i].setColor(Color::Black);
					hs[i].setCharacterSize(14);
				}
				
			}
			table.writehighscore(highscores, initial);
			window.clear();
			window.draw(goSprite);
			window.draw(healthText);
			window.draw(restart);
			window.draw(highscoreText);
			for (int i = 0; i < 5; i++)
			{
				window.draw(hs[i]);
			}
			window.display();

		} 
	}
}