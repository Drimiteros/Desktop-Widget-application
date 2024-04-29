#include "CursorSprite.h"

CursorSprite::CursorSprite()
{
	cursor.setSize(Vector2f(20, 20));
	cursor.setTextureRect(IntRect(0, 0, 5, 5));
	cursor.setOutlineColor(Color::White);
	cursor.setOutlineThickness(1);
	cursor.setFillColor(Color::Transparent);
	cursor.setOrigin(7.5, 7.5);
	buildCursor.setSize(Vector2f(15, 15));
	buildCursor.setTextureRect(IntRect(0, 0, 5, 5));
	buildCursor.setOutlineColor(Color::White);
	buildCursor.setOutlineThickness(1);
	buildCursor.setFillColor(Color::Transparent);
	buildCursor.setOrigin(7.5, 7.5);
}

CursorSprite::~CursorSprite()
{

}

void CursorSprite::mainLogic(RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
		buildCursor.setPosition(cursor.getPosition());
	cursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
}

void CursorSprite::draw(RenderWindow& window)
{
	window.draw(cursor);
	window.draw(buildCursor);
}