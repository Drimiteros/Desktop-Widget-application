#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "CursorSprite.h"

#define color_box_count 9

using namespace std;
using namespace sf;

class Get_CPU_Utilization
{
private:
	FILETIME idleTime1, kernelTime1, userTime1;
	FILETIME idleTime2, kernelTime2, userTime2;
	Vector2f difference;

	Clock updateClock;

	Font font;
	Font font2;

	double cpuUtilization;

	RectangleShape color_boxes[color_box_count];
	int r[color_box_count] = { 255,255,0  ,0  ,1,255,255,255,0 };
	int g[color_box_count] = { 255,0  ,255,0  ,0,255,0  ,145,255 };
	int b[color_box_count] = { 255,0  ,0  ,255,0,0  ,255,0  ,191 };

public:
	Text text;
	Text color_text;
	Text position_text;

	Get_CPU_Utilization();
	void calculate_CPU_Utilization(bool& edit_mode);
	void set_widget_values();
	void change_widget_position(RenderWindow& window, Clock& reference_clock, CursorSprite& cursor, bool& edit_mode);
	void change_widget_color(CursorSprite& cursor, bool& edit_mode);
	void draw(RenderWindow& window, bool& edit_mode);
};

