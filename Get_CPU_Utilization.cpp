#include "Get_CPU_Utilization.h"

Get_CPU_Utilization::Get_CPU_Utilization()
{
    font.loadFromFile("src/Fonts/font.ttf");
    font2.loadFromFile("src/Fonts/font11.ttf");
    text.setFont(font);
    text.setScale(0.5, 0.5);
    text.setCharacterSize(50);
    text.setOutlineThickness(2);
    text.setOutlineColor(Color(1, 0, 0, 255));
    text.setFillColor(Color(3, 255, 171, 255));
    text.setPosition(10, 10);
    color_text.setFont(font2);
    color_text.setScale(0.5, 0.5);
    color_text.setCharacterSize(50);
    color_text.setFillColor(Color(255, 255, 254));
    color_text.setOutlineColor(Color(0, 0, 1));
    color_text.setOutlineThickness(2);
    position_text.setFont(font2);
    position_text.setScale(0.5, 0.5);
    position_text.setCharacterSize(50);
    position_text.setFillColor(Color(255, 255, 254));
    position_text.setOutlineColor(Color(0, 0, 1));
    position_text.setOutlineThickness(2);

    for (int i = 0; i < color_box_count; i++)
    {
        color_boxes[i].setFillColor(Color(r[i], g[i], b[i]));
        color_boxes[i].setSize(Vector2f(20, 20));
        color_boxes[i].setOutlineColor(Color(255, 255, 254));
        color_boxes[i].setOutlineThickness(1);
    }
}

void Get_CPU_Utilization::calculate_CPU_Utilization(bool& edit_mode)
{
    FILETIME idleTime1, kernelTime1, userTime1;
    FILETIME idleTime2, kernelTime2, userTime2;
    
    // Get system times at the beginning of the sample
    if (!GetSystemTimes(&idleTime1, &kernelTime1, &userTime1));
    
    // Sleep for a short duration to allow some CPU usage
    if (edit_mode == false)
        this_thread::sleep_for(chrono::milliseconds(100));

    // Get system times at the end of the sample
    if (!GetSystemTimes(&idleTime2, &kernelTime2, &userTime2));
    
    // Calculate idle time between the two samples
    ULONGLONG idleTimeDelta = (reinterpret_cast<ULARGE_INTEGER*>(&idleTime2)->QuadPart - reinterpret_cast<ULARGE_INTEGER*>(&idleTime1)->QuadPart);
    
    // Calculate total time between the two samples
    ULONGLONG totalTimeDelta = (reinterpret_cast<ULARGE_INTEGER*>(&kernelTime2)->QuadPart - reinterpret_cast<ULARGE_INTEGER*>(&kernelTime1)->QuadPart) +
        (reinterpret_cast<ULARGE_INTEGER*>(&userTime2)->QuadPart - reinterpret_cast<ULARGE_INTEGER*>(&userTime1)->QuadPart);
    
    // Calculate CPU utilization percentage
    cpuUtilization = 100.0 - ((static_cast<double>(idleTimeDelta) / totalTimeDelta) * 100.0);
}

void Get_CPU_Utilization::set_widget_values()
{
    text.setString("CPU: " + to_string(cpuUtilization).substr(0, 4) + "%");
    color_text.setString("Color ");
    position_text.setString("Position: (" + to_string(int(text.getPosition().x)) + ", " + to_string(int(text.getPosition().y)) + ")");
}

void Get_CPU_Utilization::change_widget_position(RenderWindow& window, Clock& reference_clock, CursorSprite& cursor, bool& edit_mode)
{
    if (cursor.cursor.getGlobalBounds().intersects(text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && edit_mode == true)
    {
        text.setPosition(cursor.cursor.getPosition().x - difference.x, cursor.cursor.getPosition().y - difference.y);
    }
    else
    {
        difference.x = cursor.cursor.getPosition().x - text.getPosition().x;
        difference.y = cursor.cursor.getPosition().y - text.getPosition().y;
    }

    for (int i = 0; i < color_box_count && edit_mode == true; i++)
        color_boxes[i].setPosition(text.getPosition().x + (i * 30) + 80, text.getPosition().y + (1.5 * text.getGlobalBounds().getSize().y));
    color_text.setPosition(color_boxes[0].getPosition().x - 80, color_boxes[0].getPosition().y - 10);
    position_text.setPosition(color_boxes[0].getPosition().x - 80, color_boxes[0].getPosition().y + 20);
}

void Get_CPU_Utilization::change_widget_color(CursorSprite& cursor, bool& edit_mode)
{
    for (int i = 0; i < color_box_count; i++)
        if (cursor.cursor.getGlobalBounds().intersects(color_boxes[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)
            && edit_mode == true)
            text.setFillColor(Color(r[i], g[i], b[i]));
}

void Get_CPU_Utilization::draw(RenderWindow& window, bool& edit_mode)
{
    window.draw(text);
    for (int i = 0; i < color_box_count && edit_mode == true; i++)
        window.draw(color_boxes[i]);
    if (edit_mode == true)
    {
        window.draw(color_text);
        window.draw(position_text);
    }
}