#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CursorSprite.h"
#include "Get_Time.h"
#include "Get_CPU_Utilization.h"
#include "Get_RAM_Usage.h"

using namespace std;
using namespace sf;

class File_Handler
{

public:
	File_Handler();
	void save_clock_dock_settings(CursorSprite c, Get_Time& get_time, float posX, float posY, int r, int g, int b, float tcS, float ccS, float thickness, bool& active);
	void save_cpu_dock_settings(CursorSprite c, Get_CPU_Utilization& get_cpu_util, float posX, float posY, int r, int g, int b, float cS, float thickness, bool& active);
	void save_ram_dock_settings(CursorSprite c, Get_RAM_Usage& get_ram_usage, float posX, float posY, int r, int g, int b, float cS, float thickness, bool& active);
	void load_clock_dock_settings(Get_Time& get_time, bool& isActive);
	void load_cpu_dock_settings(Get_CPU_Utilization& get_cpu_util, bool& isActive);
	void load_ram_dock_settings(Get_RAM_Usage& get_ram_usage, bool& isActive);
};

