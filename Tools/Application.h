#pragma once
#include "config.h"
#include "graphics.h"
#include <stdlib.h>
class Menu;
class Game;
class Application // application has a singleton design pattern.All variables and methods of Application are global.
{
private: // the constructors and the assignment operator must be private in order to ensure that no other instance of application will be created 
	Application() {};
	Application(Application const&) {};
	Application& operator=(Application const& copy) {};
	graphics::Brush br;
public:
	float WindowWidth = WINDOW_WIDTH;
	float WindowHeight = WINDOW_HEIGHT;
	float CanvasWidth = CANVAS_WIDTH;
	float  CanvasHeight = CANVAS_HEIGHT;
	float loadingtime = 18600;
	bool loaded = false;
	Menu* menu = nullptr;
	Game* fight = nullptr;
	void setApp();
	void update(float ms = 100);
	void draw();
	void resize(int w, int h);
	void destroy();
	void setNewMenu(Menu* value);
	void setNewGame(Game* value);
	static Application& getInstance()
	{
		static Application instance;
		return instance;
	}
};


