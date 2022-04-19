#include "Application.h"
#include "Menus.h"
#include "Game.h"
void Application::setApp()
{
	menu = new StartMenu;
	graphics::createWindow(WindowWidth, WindowHeight, "FightingArcade");
	//graphics::setFullScreen(true);
	graphics::setCanvasSize(CanvasWidth, CanvasHeight);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_WINDOW);
	// application set the draw,update,and resize callbacks with std::bind 
	graphics::setDrawFunction(std::bind(&Application::draw, this));
	graphics::setUpdateFunction(std::bind(&Application::update, this, std::placeholders::_1));
	graphics::setResizeFunction(std::bind(&Application::resize, this, std::placeholders::_1, std::placeholders::_2));
	graphics::startMessageLoop();
}

void Application::update(float ms)
{
	if (menu) {
		menu->update();
	}
	if (fight) {
		fight->update();
	}
	
}

void Application::draw()
{
	if (fight)
	{
		fight->draw();
	}
	if (menu) {
		menu->draw();
	}
}

void Application::resize(int w, int h)
{
	if (menu)
	{
		menu->adjustCanvas(w, h);
	}
	if (fight)
	{
		fight->adjustCanvas(w, h);
	}
}

void Application::destroy()
{
	graphics::destroyWindow(); // after the call of destroy window menu and fight must be deleted
	delete menu;
	delete fight;
	exit(0);//exits the program through here
}

void Application::setNewMenu(Menu* value) // setNewMenu is used for deleting and assigning menu objects
{
	if (menu != value) {
		if (menu) {
			delete menu;
			menu = value;
		}
		else {
			menu = value;
		}
	}
}

void Application::setNewGame(Game* value) // setNewGame is used for deleting and assigning game objects
{
	if (fight != value) {
		if (fight) {
			delete fight;
			fight = value;
		}
		else {
			fight = value;
		}
	}
}



