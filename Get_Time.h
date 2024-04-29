#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <ctime>
#include "CursorSprite.h"

#define color_box_count 9

#pragma warning(disable : 4996)

using namespace std;
using namespace sf;

class Get_Time
{
private:
	time_t current_time;
	tm* local_time;
	string day_array[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday" , "Friday", "Saturday" };
	string active_day;
	int active_day_number;
	string month_array[12] = { "January", "February", "March", "April", "May" , "June", "July", "August", "September", "October", "November", "December" };
	string active_month;
	Vector2f difference;

	Font font;
	Font font2;

	RectangleShape color_boxes[color_box_count];
	int r[color_box_count] = { 255,255,0  ,0  ,1,255,255,255,0   };
	int g[color_box_count] = { 255,0  ,255,0  ,0,255,0  ,145,255 };
	int b[color_box_count] = { 255,0  ,0  ,255,0,0  ,255,0  ,191 };

public:
	Text time_text;
	Text time_color_text;
	Text time_position_text;
	Text calendar_text;

	Get_Time();
	void calculate_time();
	void calculate_day();
	void calculate_month();
	void set_widget_values();
	void init_widget_position(RenderWindow& window);
	void change_widget_position(RenderWindow& window, Clock& reference_clock, CursorSprite& cursor, bool& edit_mode);
	void change_widget_color(CursorSprite& cursor, bool& edit_mode);
	void draw(RenderWindow& window, bool& edit_mode);
};

