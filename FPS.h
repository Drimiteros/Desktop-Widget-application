#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class FPS
{
private:
	Font font;
	RectangleShape b;

public:
	//FPS
	Text fpsText;
	Time time;
	Clock fpsClock;
	Clock clock;
	bool sFPS = true;

	FPS();
	~FPS();
	void logic(RenderWindow& window);
	void draw(RenderWindow& window);
};

