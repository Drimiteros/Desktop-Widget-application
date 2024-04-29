#include "Renderer.h"

Renderer::Renderer()
{
	//Initialize window
	Vector2u screenSize = Vector2u(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	window.create(VideoMode(screenSize.x - 1, screenSize.y - 1), "Dock", Style::None);
	window.setPosition(Vector2i(0, 0));

	//Get the native window handle and make the window not accessable using Alt + Tab
	hwnd = window.getSystemHandle();
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_POPUP | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	// Extend the glass frame into the client area
	margins = { -1, -1, -1, -1 }; // Extend margins from all sides
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	//Set the window as bottommost
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	//Init first time dock preferences
	get_time.init_widget_position(window);
}

void Renderer::events()
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void Renderer::main_loop()
{
	while (window.isOpen())
	{
		events();

		window.clear(Color::Transparent);

		update_logic();
		draw_layer1();
		draw_layer2();

		window.display();
	}
}

void Renderer::update_logic()
{
	//Cursor logic
	cursor.mainLogic(window);
	if (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right))
		SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	//FPS logic
	fps.logic(window);

	//Edit mode logic
	if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::LShift))
		edit_mode = true;
	else
		edit_mode = false;

	//Main Widget logic
	if (isTimeWidgetActive == true)
	{
		get_time.calculate_time();
		get_time.calculate_day();
		get_time.calculate_month();
		get_time.set_widget_values();
		get_time.change_widget_position(window, reference_clock, cursor, edit_mode);
		get_time.change_widget_color(cursor, edit_mode);
	}
	if (isCpuWidgetActive == true)
	{
		cpu_utilization.calculate_CPU_Utilization(edit_mode);
		cpu_utilization.set_widget_values();
		cpu_utilization.change_widget_position(window, reference_clock, cursor, edit_mode);
		cpu_utilization.change_widget_color(cursor, edit_mode);
	}
	if (isRamWidgetActive == true)
	{
		get_ram_usage.calculate_RAM_Usage();
		get_ram_usage.set_widget_values();
		get_ram_usage.change_widget_position(window, reference_clock, cursor, edit_mode);
		get_ram_usage.change_widget_color(cursor, edit_mode);
	}

	//Save dock settings
	file_handler.save_clock_dock_settings(cursor, get_time, get_time.time_text.getPosition().x, get_time.time_text.getPosition().y, get_time.time_text.getFillColor().r, get_time.time_text.getFillColor().g, get_time.time_text.getFillColor().b, get_time.time_text.getCharacterSize(), get_time.calendar_text.getCharacterSize(), get_time.time_text.getOutlineThickness(), isTimeWidgetActive);
	file_handler.save_cpu_dock_settings(cursor, cpu_utilization, cpu_utilization.text.getPosition().x, cpu_utilization.text.getPosition().y, cpu_utilization.text.getFillColor().r, cpu_utilization.text.getFillColor().g, cpu_utilization.text.getFillColor().b, cpu_utilization.text.getCharacterSize(), cpu_utilization.text.getOutlineThickness(), isCpuWidgetActive);
	file_handler.save_ram_dock_settings(cursor, get_ram_usage, get_ram_usage.text.getPosition().x, get_ram_usage.text.getPosition().y, get_ram_usage.text.getFillColor().r, get_ram_usage.text.getFillColor().g, get_ram_usage.text.getFillColor().b, get_ram_usage.text.getCharacterSize(), get_ram_usage.text.getOutlineThickness(), isRamWidgetActive);

	//Load dock settings
	file_handler.load_clock_dock_settings(get_time, isTimeWidgetActive);
	file_handler.load_cpu_dock_settings(cpu_utilization, isCpuWidgetActive);
	file_handler.load_ram_dock_settings(get_ram_usage, isRamWidgetActive);
}

void Renderer::draw_layer1()
{

}

void Renderer::draw_layer2()
{
	if (isTimeWidgetActive == true)
		get_time.draw(window, edit_mode);
	if (isCpuWidgetActive == true)
		cpu_utilization.draw(window, edit_mode);
	if (isRamWidgetActive == true)
		get_ram_usage.draw(window, edit_mode);
}