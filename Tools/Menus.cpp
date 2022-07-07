#include "Menus.h"
#include "Application.h"
#include "Game.h"


void StartMenu::update()
{
	if (start) {
		graphics::playSound(std::string(ASSET_PATH) + "Start.wav", 0.5f, false);
		graphics::playMusic(std::string(ASSET_PATH) + "welcometofighterx.wav", 0.6f, false);
		start = false;
	}

	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		// this is the fight option for setting a new choose fighter menu
		if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 100) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 100) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 - 100) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2))
		{
			graphics::playSound(std::string(ASSET_PATH) + "menuchoice.wav", 0.5f, false);
			Menu* menu = new ChooseFighterMenu;
			Application::getInstance().setNewMenu(menu);
		}
		// this is the quit option for exiting the program
		else if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 100) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 100) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 + 50) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2 + 150)) {
			Application::getInstance().setNewMenu(nullptr);
			Application::getInstance().destroy();
		}
	}

}
StartMenu::StartMenu() {
	background.texture = std::string(ASSET_PATH) + "menu.png";
	option1.texture = std::string(ASSET_PATH) + "fightoption.png";
	option1.outline_opacity = 0.0f;
	header.texture = std::string(ASSET_PATH) + "welcome.png";
	option2.texture = std::string(ASSET_PATH) + "quitoption.png";
	option2.outline_opacity = 0.0f;
}
void StartMenu::draw() {

	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight, background);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 200, 800, 75, header);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 50, 200, 100, option1);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 + 100, 200, 100, option2);


}
void StartMenu::adjustCanvas(int new_w, int new_h)
{
	Application::getInstance().CanvasWidth = new_w;
	Application::getInstance().CanvasHeight = new_h;
}






void ChooseFighterMenu::adjustCanvas(int new_w, int new_h)
{
	Application::getInstance().CanvasWidth = new_w;
	Application::getInstance().CanvasHeight = new_h;
}



ChooseFighterMenu::ChooseFighterMenu()
{
	background.texture = std::string(ASSET_PATH) + "menu.png";
	option1.texture = std::string(ASSET_PATH) + "mugshot1.png";
	option1.outline_opacity = 0.0f;
	header.texture = std::string(ASSET_PATH) + "chooseyourfighter.png";
	option2.texture = std::string(ASSET_PATH) + "mugshot2.png";
	option2.outline_opacity = 0.0f;
	goback.texture = std::string(ASSET_PATH) + "goback.png";
	goback.outline_opacity = 0.0f;
	graphics::playMusic(std::string(ASSET_PATH) + "chooseyourfighter.wav", 0.7f, false);

}

void ChooseFighterMenu::update()
{
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		//file animation 1 and fileanimation 2 are used for seperating the two animation folders: file animation 1 is for the player's choice the other will be the ai
		// option for choosing bison
		if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 450) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 - 150) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 - 98) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2 + 398))
		{
			graphics::playSound(std::string(ASSET_PATH) + "choose_bison.wav", 0.4f, false);
			Menu* menu = new ChooseMap();
			menu->fileanimation1 = "bison\\";
			menu->fileanimation2 = "ken\\";
			Application::getInstance().setNewMenu(menu);
		}
		// option for choosing ken
		else if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 + 150) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 450) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 - 98) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2 + 398))
		{
			graphics::playSound(std::string(ASSET_PATH) + "Ryu_choose.wav", 0.4f, false);
			Menu* menu = new ChooseMap();
			menu->fileanimation1 = "ken\\";
			menu->fileanimation2 = "bison\\";
			Application::getInstance().setNewMenu(menu);

		}
		// go back to the start menu
		else if (mouse.cur_pos_x >= 75 - 75 && mouse.cur_pos_x <= 75 + 75 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight - 50 - 50 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight - 50 + 50) {
			graphics::playSound(std::string(ASSET_PATH) + "menuchoice.wav", 0.4f, false);
			Menu* menu = new StartMenu;
			Application::getInstance().setNewMenu(menu);
		}
	}
}

void ChooseFighterMenu::draw()
{

	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight, background);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 200, 800, 75, header);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2 - 300, Application::getInstance().CanvasHeight / 2 + 100, 300, 396, option1);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2 + 300, Application::getInstance().CanvasHeight / 2 + 100, 300, 396, option2);
	graphics::drawRect(75, Application::getInstance().CanvasHeight - 50, 150, 100, goback);
}

void ChooseMap::adjustCanvas(int new_w, int new_h)
{
	Application::getInstance().CanvasWidth = new_w;
	Application::getInstance().CanvasHeight = new_h;
}

ChooseMap::ChooseMap()
{
	header.texture = std::string(ASSET_PATH) + "choosemap.png";
	background.fill_color[0] = 0.2f;
	background.fill_color[1] = 0.2f;
	background.fill_color[2] = 0.2f;
	background.outline_opacity = 0.0f;
	option1.texture = std::string(ASSET_PATH) + "summerbrawl.png";
	option1.outline_opacity = 1.0f;
	option2.texture = std::string(ASSET_PATH) + "metalfest.png";
	option2.outline_opacity = 1.0f;
	option3.texture = std::string(ASSET_PATH) + "dragonstemple.png";
	option3.outline_opacity = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "Dragon Wings.ttf");
	text.fill_color[0] = 0.6f;
	text.fill_color[1] = 0.5f;
	text.fill_color[2] - 0.7f;
	goback.texture = std::string(ASSET_PATH) + "goback.png";
	goback.outline_opacity = 0.0f;
	graphics::playMusic(std::string(ASSET_PATH) + "choosemap.wav", 1.0f, false);

}

void ChooseMap::update()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		// this is the summerbrawl option which creates a new game object and sets the right animation folder for each fighter fileanimation 1 is the player's animation folder file animation 2 is the ai's animation folder
		if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 100) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 100) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 - 100) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2))
		{
			graphics::playSound(std::string(ASSET_PATH) + "summerbrawl.wav", 1.0f, false);
			Game* fight = new Game("summerbrawl.png", 10, fileanimation1, fileanimation2);
			fight->adjustCanvas(Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight);
			Application::getInstance().setNewGame(fight);
			Application::getInstance().setNewMenu(nullptr);
			graphics::playMusic(std::string(ASSET_PATH) + "summerbrawl_music.mp3", 0.2f, true);
		}
		// this is the metal fest option
		else if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 100) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 100) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 + 50) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2 + 150))
		{
			graphics::playSound(std::string(ASSET_PATH) + "metalfest.wav", 1.0f, false);
			Game* fight = new Game("metalfest.png", 8, fileanimation1, fileanimation2);
			fight->adjustCanvas(Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight);
			Application::getInstance().setNewGame(fight);
			Application::getInstance().setNewMenu(nullptr);
			graphics::playMusic(std::string(ASSET_PATH) + "metalfest_music.mp3", 0.7f, true);
		}
		// this is the dragon's temple option
		else if (mouse.cur_pos_x >= (Application::getInstance().CanvasWidth / 2 - 100) && mouse.cur_pos_x <= (Application::getInstance().CanvasWidth / 2 + 100) && mouse.cur_pos_y >= (Application::getInstance().CanvasHeight / 2 + 200) && mouse.cur_pos_y <= (Application::getInstance().CanvasHeight / 2 + 300))
		{
			graphics::playSound(std::string(ASSET_PATH) + "dragonstemple.wav", 1.0f, false);
			Game* fight = new Game("dragonstemple.png", 8, fileanimation1, fileanimation2);
			fight->adjustCanvas(Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight);
			Application::getInstance().setNewGame(fight);
			Application::getInstance().setNewMenu(nullptr);
			graphics::playMusic(std::string(ASSET_PATH) + "dragonstemple_music.mp3", 0.2f, true);
		}
		//this is the go back to choose fighter menu option
		else if (mouse.cur_pos_x >= 75 - 75 && mouse.cur_pos_x <= 75 + 75 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight - 50 - 50 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight - 50 + 50) {
			graphics::playSound(std::string(ASSET_PATH) + "menuchoice.wav", 0.4f, false);
			ChooseFighterMenu* menu = new ChooseFighterMenu();
			Application::getInstance().setNewMenu(menu);
		}
	}
}

void ChooseMap::draw()
{
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight, background);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 200, 800, 75, header);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 50, 200, 100, option1);
	graphics::drawText(Application::getInstance().CanvasWidth / 2 - 83, Application::getInstance().CanvasHeight / 2 + 25, 30, "Summerbrawl", text);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 + 100, 200, 100, option2);
	graphics::drawText(Application::getInstance().CanvasWidth / 2 - 65, Application::getInstance().CanvasHeight / 2 + 175, 30, "Metal fest", text);
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 + 250, 200, 100, option3);
	graphics::drawText(Application::getInstance().CanvasWidth / 2 - 96, Application::getInstance().CanvasHeight / 2 + 325, 30, "Dragon's temple", text);
	graphics::drawRect(75, Application::getInstance().CanvasHeight - 50, 150, 100, goback);

}
