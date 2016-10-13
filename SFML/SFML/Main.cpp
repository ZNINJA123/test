#include<stdlib.h>
#include<iostream>
#include<string>
#include<SFML\Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode (400, 400), "window");
	CircleShape c;
	c.setFillColor(Color::Red);
	c.setRadius(100);
	c.setPosition(100, 100);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(c);
		window.display();

	}









	return 0;
}