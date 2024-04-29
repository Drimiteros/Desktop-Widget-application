#include "FPS.h"

FPS::FPS()
{
	//INIT FONT
	font.loadFromFile("src/Fonts/font.ttf");

	//FPS
	fpsText.setFont(font);
	fpsText.setCharacterSize(65);
	fpsText.setScale(0.2, 0.2);
	fpsText.setFillColor(Color::White);
	fpsText.setOutlineColor(Color::Black);
	fpsText.setOutlineThickness(15);
}

FPS::~FPS()
{

}

void FPS::logic(RenderWindow& w)
{
	//FPS
	time = fpsClock.getElapsedTime();
	fpsClock.restart().asSeconds();
	if (clock.getElapsedTime().asSeconds() > 0.3)
	{
		fpsText.setString("FPS: " + to_string(int(1.0f / time.asSeconds())));
		clock.restart();
	}
	fpsText.setPosition(w.mapPixelToCoords(Vector2i(15, 15)));
}

void FPS::draw(RenderWindow& window)
{
	if (sFPS == true)
		window.draw(fpsText);
}