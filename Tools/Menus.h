#pragma once
# include "graphics.h"
class Menu { // menu is an abstract class that is a parent of StartMenu,ChooseFighterMenu,ChooseMapMenu and calls each method virtually 
protected:
	graphics::Brush  background, option1, header, option2, option3, text,goback;
	graphics::MouseState mouse;
public:
	void virtual adjustCanvas(int new_w, int new_h) = 0;
	void virtual draw()= 0;
	void virtual update() = 0;
	std::string fileanimation1, fileanimation2 = "";
};


class StartMenu: public Menu  {
private:
	bool start = true;
public:
	StartMenu();
	void adjustCanvas(int new_w, int new_h);
	void draw();
	void update(); 
};

class ChooseFighterMenu : public Menu {
public:
	ChooseFighterMenu();
	void adjustCanvas(int new_w, int new_h);
	void update();
	void draw();
};


class ChooseMap :public Menu {
public:
	ChooseMap();
	void adjustCanvas(int new_w, int new_h);
	void update();
	void draw();
	
};
