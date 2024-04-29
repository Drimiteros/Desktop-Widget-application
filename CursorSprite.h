#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class CursorSprite
{
private:

public:
	RectangleShape cursor;
	RectangleShape buildCursor;
	int state = 0;
	bool selected = false;
	Clock selectedClock;

	CursorSprite();
	~CursorSprite();
	void mainLogic(RenderWindow& window);
	void draw(RenderWindow& window);
};

