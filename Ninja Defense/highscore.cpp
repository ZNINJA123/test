#include "highscore.h"
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include"SFML\Graphics.hpp"
using namespace sf;
using namespace std;




highscore::highscore()
{
}


highscore::~highscore()
{

}


void highscore::readhighscore(std::string * v, std::string * s, int size)
{
	std::ifstream file;
	file.open("highscore.txt");
	if (file.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			file >> s[i];
			file >> v[i];
		}
	}

}

void highscore::writehighscore(std::string * v, std::string * s)
{
	ofstream file;
	file.open("highscore.txt",ofstream::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			file << s[i];
			file << "\r\n"; 
			file << v[i];
			file << "\r\n";
		}
	}
	file.close();
}