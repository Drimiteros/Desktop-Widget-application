#include "Get_RAM_Usage.h"

Get_RAM_Usage::Get_RAM_Usage()
{
    font.loadFromFile("src/Fonts/font.ttf");
    font2.loadFromFile("src/Fonts/font11.ttf");
    text.setFont(font);
    text.setScale(0.5, 0.5);
    text.setCharacterSize(50);
    text.setOutlineThickness(2);
    text.setOutlineColor(Color(1, 0, 0, 255));
    text.setFillColor(Color(3, 255, 171, 255));
    text.setPosition(10, 30);
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

void Get_RAM_Usage::calculate_RAM_Usage()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        DWORDLONG totalPhysicalMemory = memoryStatus.ullTotalPhys; // Total physical memory in bytes
        DWORDLONG freePhysicalMemory = memoryStatus.ullAvailPhys; // Free physical memory in bytes

        // Calculate used physical memory
        DWORDLONG usedPhysicalMemory = totalPhysicalMemory - freePhysicalMemory;

        // Convert bytes to megabytes (1 MB = 1024 * 1024 bytes)
        totalPhysicalMemoryGB = totalPhysicalMemory / (1024.0 * 1024.0 * 1024.0);
        usedPhysicalMemoryGB = usedPhysicalMemory / (1024.0 * 1024.0 * 1024.0);
    }
    else
        cerr << "Failed to retrieve memory status." << endl;

    float usage = (usedPhysicalMemoryGB * 100) / totalPhysicalMemoryGB;

    text.setString("RAM: " + to_string(usage).substr(0, 4) + "%");
}

void Get_RAM_Usage::set_widget_values()
{
    color_text.setString("Color ");
    position_text.setString("Position: (" + to_string(int(text.getPosition().x)) + ", " + to_string(int(text.getPosition().y)) + ")");
}

void Get_RAM_Usage::change_widget_position(RenderWindow& window, Clock& reference_clock, CursorSprite& cursor, bool& edit_mode)
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

void Get_RAM_Usage::change_widget_color(CursorSprite& cursor, bool& edit_mode)
{
    for (int i = 0; i < color_box_count; i++)
        if (cursor.cursor.getGlobalBounds().intersects(color_boxes[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)
            && edit_mode == true)
            text.setFillColor(Color(r[i], g[i], b[i]));
}

void Get_RAM_Usage::draw(RenderWindow& window, bool& edit_mode)
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