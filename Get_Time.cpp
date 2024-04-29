#include "Get_Time.h"

Get_Time::Get_Time()
{
	font.setSmooth(true);
	font2.setSmooth(true);
	font.loadFromFile("src/Fonts/font.ttf");
	font2.loadFromFile("src/Fonts/font11.ttf");
	time_text.setFont(font);
	time_text.setScale(0.5, 0.5);
	time_text.setCharacterSize(80);
	time_text.setOutlineThickness(2);
	time_text.setOutlineColor(Color(1, 0, 0, 255));
	time_text.setFillColor(Color(3, 255, 171, 255));
	time_color_text.setFont(font2);
	time_color_text.setScale(0.5, 0.5);
	time_color_text.setCharacterSize(50);
	time_color_text.setFillColor(Color(255, 255, 254));
	time_color_text.setOutlineColor(Color(0, 0, 1));
	time_color_text.setOutlineThickness(2);
	time_position_text.setFont(font2);
	time_position_text.setScale(0.5, 0.5);
	time_position_text.setCharacterSize(50);
	time_position_text.setFillColor(Color(255, 255, 254));
	time_position_text.setOutlineColor(Color(0, 0, 1));
	time_position_text.setOutlineThickness(2);
	calendar_text.setFont(font);
	calendar_text.setScale(0.5, 0.5);
	calendar_text.setCharacterSize(time_text.getCharacterSize() - 30);
	calendar_text.setOutlineThickness(2);
	calendar_text.setOutlineColor(Color(1, 0, 0, 255));
	calendar_text.setFillColor(Color(3, 255, 171, 255));

	for (int i = 0; i < color_box_count; i++)
	{
		color_boxes[i].setFillColor(Color(r[i], g[i], b[i]));
		color_boxes[i].setSize(Vector2f(20, 20));
		color_boxes[i].setOutlineColor(Color(255, 255, 254));
		color_boxes[i].setOutlineThickness(1);
	}
}

void Get_Time::calculate_time()
{
	current_time = time(nullptr); //Get current time as the number of seconds since the epoch (January 1, 1970).
	local_time = localtime(&current_time); //Convert current_time to local time
}

void Get_Time::calculate_day()
{
	active_day = day_array[local_time->tm_wday]; //Get the active day of the week
	active_day_number = local_time->tm_mday; //Get the active date of the month
}

void Get_Time::calculate_month()
{
	active_month = month_array[local_time->tm_mon]; //Get the active month
}

void Get_Time::set_widget_values()
{
	//Set the local time as a string of the var time_text that will be displayed in the screen
	if (local_time->tm_min < 10)
		time_text.setString(to_string(local_time->tm_hour) + ":0" + to_string(local_time->tm_min));
	else
		time_text.setString(to_string(local_time->tm_hour) + ":" + to_string(local_time->tm_min));
	calendar_text.setString(active_day + ", " + to_string(active_day_number) + " " + active_month + " " + to_string(local_time->tm_year + 1900));

	time_color_text.setString("Color ");
	time_position_text.setString("Position: (" + to_string(int(time_text.getPosition().x)) + ", " + to_string(int(time_text.getPosition().y)) + ")");
}

void Get_Time::init_widget_position(RenderWindow& window)
{
	time_text.setPosition(window.getSize().x / 2 - (time_text.getString().getSize() * time_text.getCharacterSize() * time_text.getScale().x) / 8.5, 10);
}

void Get_Time::change_widget_position(RenderWindow& window, Clock& reference_clock, CursorSprite& cursor, bool& edit_mode)
{
	//Update the text position dynamicaly, based on they character size
	calendar_text.setPosition((time_text.getPosition().x + (time_text.getGlobalBounds().getSize().x) / 1.9) - (calendar_text.getGlobalBounds().getSize().x) / 2, time_text.getPosition().y + time_text.getGlobalBounds().getSize().y * 2);
	
	if ((cursor.cursor.getGlobalBounds().intersects(time_text.getGlobalBounds()) || cursor.cursor.getGlobalBounds().intersects(calendar_text.getGlobalBounds()))
		&& Mouse::isButtonPressed(Mouse::Left) && edit_mode == true)
	{
		time_text.setPosition(cursor.cursor.getPosition().x - difference.x, cursor.cursor.getPosition().y - difference.y);
	}
	else
	{
		difference.x = cursor.cursor.getPosition().x - time_text.getPosition().x;
		difference.y = cursor.cursor.getPosition().y - time_text.getPosition().y;
	}

	for (int i = 0; i < color_box_count && edit_mode == true; i++)
		color_boxes[i].setPosition(calendar_text.getPosition().x + (i * 30) + 80, calendar_text.getPosition().y + (1.5 * time_text.getGlobalBounds().getSize().y));
	time_color_text.setPosition(color_boxes[0].getPosition().x - 80, color_boxes[0].getPosition().y - 10);
	time_position_text.setPosition(color_boxes[0].getPosition().x - 80, color_boxes[0].getPosition().y + 20);
}

void Get_Time::change_widget_color(CursorSprite& cursor, bool& edit_mode)
{
	for (int i = 0; i < color_box_count; i++)
	{
		if (edit_mode == true && 
			cursor.cursor.getGlobalBounds().intersects(color_boxes[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			time_text.setFillColor(Color(r[i], g[i], b[i]));
			calendar_text.setFillColor(Color(r[i], g[i], b[i]));
		}
	}
}

void Get_Time::draw(RenderWindow& window, bool& edit_mode)
{
	//Draw the texts
	window.draw(time_text);
	window.draw(calendar_text);
	for (int i = 0; i < color_box_count && edit_mode == true; i++)
		window.draw(color_boxes[i]);
	if (edit_mode == true)
	{
		window.draw(time_color_text);
		window.draw(time_position_text);
	}
}