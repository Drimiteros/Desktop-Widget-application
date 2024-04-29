#include "File_Handler.h"

File_Handler::File_Handler()
{

}

void File_Handler::save_clock_dock_settings(CursorSprite c, Get_Time& get_time, float posX, float posY, int r, int g, int b, float tcS, 
	float ccS, float thickness, bool& active)
{
	if (c.cursor.getGlobalBounds().intersects(get_time.time_text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
	{
		ofstream dock("src/Saves/time_dock.txt");
		if (dock.is_open())
		{
			dock.clear();
			dock << "Load Current Profile:1" << endl;
			dock << "Is active:" << active << endl;
			dock << "PositionX:" << posX << "\nPositionY:" << posY << endl;
			dock << "R:" << r << "\nG:" << g << "\nB:" << b << endl;
			dock << "Time Character Size:" << tcS << endl;
			dock << "Calendar Character Size:" << ccS << endl;
			dock << "Outline Thicknes:" << thickness << endl;
		}
		dock.close();
	}
}

void File_Handler::save_cpu_dock_settings(CursorSprite c, Get_CPU_Utilization& get_cpu_util, float posX, float posY, int r, int g, int b, 
	float cS, float thickness, bool& active)
{
	if (c.cursor.getGlobalBounds().intersects(get_cpu_util.text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
	{
		ofstream dock("src/Saves/cpu_dock.txt");
		if (dock.is_open())
		{
			dock.clear();
			dock << "Load Current Profile:1" << endl;
			dock << "Is active:" << active << endl;
			dock << "PositionX:" << posX << "\nPositionY:" << posY << endl;
			dock << "R:" << r << "\nG:" << g << "\nB:" << b << endl;
			dock << "Character Size:" << cS << endl;
			dock << "Outline Thicknes:" << thickness << endl;
		}
		dock.close();
	}
}

void File_Handler::save_ram_dock_settings(CursorSprite c, Get_RAM_Usage& get_ram_usage, float posX, float posY, int r, int g, int b, float cS,
	float thickness, bool& active)
{
	if (c.cursor.getGlobalBounds().intersects(get_ram_usage.text.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
	{
		ofstream dock("src/Saves/ram_dock.txt");
		if (dock.is_open())
		{
			dock.clear();
			dock << "Load Current Profile:1" << endl;
			dock << "Is active:" << active << endl;
			dock << "PositionX:" << posX << "\nPositionY:" << posY << endl;
			dock << "R:" << r << "\nG:" << g << "\nB:" << b << endl;
			dock << "Character Size:" << cS << endl;
			dock << "Outline Thicknes:" << thickness << endl;
		}
		dock.close();
	}
}

void File_Handler::load_clock_dock_settings(Get_Time& get_time, bool& isActive)
{
	float posX, posY, tcS, ccS, thickness;
	int load = 0, r, g, b;

	ifstream dock("src/Saves/time_dock.txt");
	if (dock.is_open())
	{
		string line;
		while (getline(dock, line))
		{
			if (line.find("Load Current Profile:") != string::npos)
				load = stoi(line.substr(21, 24));
			else if (line.find("Is active:") != string::npos)
				isActive = stof(line.substr(10, 12));
			else if (line.find("PositionX:") != string::npos)
				posX = stof(line.substr(10, 20));
			else if (line.find("PositionY:") != string::npos)
				posY = stof(line.substr(10, 20));
			else if (line.find("R:") != string::npos)
				r = stoi(line.substr(2, 5));
			else if (line.find("G:") != string::npos)
				g = stoi(line.substr(2, 5));
			else if (line.find("B:") != string::npos)
				b = stoi(line.substr(2, 5));
			else if (line.find("Time Character Size:") != string::npos)
				tcS = stof(line.substr(20, 23));
			else if (line.find("Calendar Character Size:") != string::npos)
				ccS = stof(line.substr(24, 27));
			else if (line.find("Outline Thicknes:") != string::npos)
				thickness = stof(line.substr(17, 21));
		}
	}
	dock.close();
	if (load == 1)
	{
		get_time.time_text.setPosition(posX, posY);
		get_time.time_text.setFillColor(Color(r, g, b));
		get_time.time_text.setCharacterSize(tcS);
		get_time.time_text.setOutlineThickness(thickness);
		get_time.calendar_text.setFillColor(Color(r, g, b));
		get_time.calendar_text.setCharacterSize(get_time.time_text.getCharacterSize() - 300);
		get_time.calendar_text.setOutlineThickness(thickness);
		get_time.calendar_text.setCharacterSize(ccS);
	}
}

void File_Handler::load_cpu_dock_settings(Get_CPU_Utilization& get_cpu_util, bool& isActive)
{
	float posX, posY, cS, thickness;
	int load = 0, r, g, b;

	ifstream dock("src/Saves/cpu_dock.txt");
	if (dock.is_open())
	{
		string line;
		while (getline(dock, line))
		{
			if (line.find("Load Current Profile:") != string::npos)
				load = stoi(line.substr(21, 24));
			else if (line.find("Is active:") != string::npos)
				isActive = stof(line.substr(10, 12));
			else if (line.find("PositionX:") != string::npos)
				posX = stof(line.substr(10, 20));
			else if (line.find("PositionY:") != string::npos)
				posY = stof(line.substr(10, 20));
			else if (line.find("R:") != string::npos)
				r = stoi(line.substr(2, 5));
			else if (line.find("G:") != string::npos)
				g = stoi(line.substr(2, 5));
			else if (line.find("B:") != string::npos)
				b = stoi(line.substr(2, 5));
			else if (line.find("Character Size:") != string::npos)
				cS = stof(line.substr(15, 19));
			else if (line.find("Outline Thicknes:") != string::npos)
				thickness = stof(line.substr(17, 21));
		}
	}
	dock.close();
	if (load == 1)
	{
		get_cpu_util.text.setPosition(posX, posY);
		get_cpu_util.text.setFillColor(Color(r, g, b));
		get_cpu_util.text.setCharacterSize(cS);
		get_cpu_util.text.setOutlineThickness(thickness);
	}
}

void File_Handler::load_ram_dock_settings(Get_RAM_Usage& get_ram_usage, bool& isActive)
{
	float posX, posY, cS, thickness;
	int load = 0, r, g, b;

	ifstream dock("src/Saves/ram_dock.txt");
	if (dock.is_open())
	{
		string line;
		while (getline(dock, line))
		{
			if (line.find("Load Current Profile:") != string::npos)
				load = stoi(line.substr(21, 24));
			else if (line.find("Is active:") != string::npos)
				isActive = stof(line.substr(10, 12));
			else if (line.find("PositionX:") != string::npos)
				posX = stof(line.substr(10, 20));
			else if (line.find("PositionY:") != string::npos)
				posY = stof(line.substr(10, 20));
			else if (line.find("R:") != string::npos)
				r = stoi(line.substr(2, 5));
			else if (line.find("G:") != string::npos)
				g = stoi(line.substr(2, 5));
			else if (line.find("B:") != string::npos)
				b = stoi(line.substr(2, 5));
			else if (line.find("Character Size:") != string::npos)
				cS = stof(line.substr(15, 19));
			else if (line.find("Outline Thicknes:") != string::npos)
				thickness = stof(line.substr(17, 21));
		}
	}
	dock.close();
	if (load == 1)
	{
		get_ram_usage.text.setPosition(posX, posY);
		get_ram_usage.text.setFillColor(Color(r, g, b));
		get_ram_usage.text.setCharacterSize(cS);
		get_ram_usage.text.setOutlineThickness(thickness);
	}
}