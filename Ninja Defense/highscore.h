#pragma once
#include <string>
class highscore
{
public:
	highscore();
	~highscore();

	void readhighscore(std::string * v, std::string * s, int size);
	void writehighscore(std::string * v, std::string * s);


};