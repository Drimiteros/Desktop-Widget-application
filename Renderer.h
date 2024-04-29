#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Dwmapi.h>
#include "CursorSprite.h"
#include "Get_Time.h"
#include "Get_CPU_Utilization.h"
#include "Get_RAM_Usage.h"
#include "File_Handler.h"
#include "FPS.h"
#include "thread"

#pragma comment (lib, "Dwmapi.lib") //LINK THE Dwmapi LIBRARY AGAINS THE PROGRAM (OPTIONAL)

using namespace std;
using namespace sf;

class Renderer
{
private:
	//Create window and event
	RenderWindow window;
	Event event;
	HWND hwnd;
	MARGINS margins; //INITIALIZE MARGINS

	bool edit_mode = false;
	bool isTimeWidgetActive = false;
	bool isCpuWidgetActive = false;
	bool isRamWidgetActive = false;
	//Holds the value that coresponds to the currently selected widget
	int selected_widget = 0;

	//Init FPS
	FPS fps;

	//Create a general refernce clock
	Clock reference_clock;

	//Set up cursor
	CursorSprite cursor;

	//Get time
	Get_Time get_time;

	//Get cpu utilization
	Get_CPU_Utilization cpu_utilization;

	//Get ram usage
	Get_RAM_Usage get_ram_usage;

	//Define file handler
	File_Handler file_handler;

public:

	Renderer();
	void events();
	void main_loop();
	void update_logic();
	void draw_layer1();
	void draw_layer2();
};

