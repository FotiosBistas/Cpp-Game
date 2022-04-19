#include "Game.h"
#include "Player.h"
#include "Menus.h"
#include "AI.h"
#include <random>

void Game::draw()
{
	//set scale decides which direction the ai and the player must be drawn accordingly to their x coordinates
	BackgroundAnimation(mapname, mapframes, 100); // the background does an animation during roundend , playtime and during pause time
	if (graphics::getGlobalTime() <= loading + Application::getInstance().loadingtime) { // this is the loading screen
		Application::getInstance().loaded = false;
		if (ai && player) {
			player->draw();
			ai->draw();
		}
		if (Application::getInstance().loadingtime == 18600) {
			AssetWarmUp();
		} // loading time is a global variable in application.h
	}
	else if (!Application::getInstance().loaded) {
		Application::getInstance().loaded = true;
		if (Application::getInstance().loadingtime == 18600) { Application::getInstance().loadingtime = 10000; } // this is used for the loading screen to not call asset warm up more than once during the runtime of the program because all the assets are already loaded 3 times
		timebetweenrounds = graphics::getGlobalTime(); // sets the wait time until the round 1 intro ends
	}
	if (Application::getInstance().loaded && ai && player) { 
		if (roundwait) {// waits for the countdown of the rounds to start the fight
			graphics::setScale(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			player->animation("idle", 4, 100);
			graphics::setScale(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			ai->animation("idle", 4, 100);
			player->drawLife();
			ai->drawLife();
			if (countdown_num == 4)// is the countdown hasn't started 
			{
				graphics::playSound(std::string(ASSET_PATH) + "round" + std::to_string(roundnumber) + "fight.wav", 0.5f, false);
				player->setX(Application::getInstance().CanvasWidth / 7);
				ai->setX(Application::getInstance().CanvasWidth / 7 * 6);
				player->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
				ai->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
				ai->clear();
			}
			if (graphics::getGlobalTime() >= timebetweenrounds + 3000) {
				roundwait = false; // sets the roundwait to false if 3 seconds pass
			}
			else
			{
				// this is the countdown
				if (graphics::getGlobalTime() <= timebetweenrounds + 1200) {
					countdown_num = 3;
					graphics::playSound(std::string(ASSET_PATH) + "clock.wav", 0.5f);
				}
				else if (graphics::getGlobalTime() <= timebetweenrounds + 2400) {
					countdown_num = 2;
					graphics::playSound(std::string(ASSET_PATH) + "clock.wav", 0.5f);
				}
				else {
					countdown_num = 1;
					graphics::playSound(std::string(ASSET_PATH) + "clock.wav", 0.5f);
				}
				graphics::resetPose();
				graphics::drawText(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, 150.0f, std::to_string(countdown_num), countdown);
			}
		}
		else if (roundEnd()) { // draws the round end state
			player->drawLife();
			ai->drawLife();
			if (player->getY() != Application::getInstance().CanvasHeight / 7 * 4.7 || player->getY() != Application::getInstance().CanvasHeight / 7 * 4.7) {
				player->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
				ai->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
			}
			if (player->getLife() == 0 && ai->getLife() != 0)
			{
				graphics::setScale(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
				if (Playerfilename == "bison\\") {
					if (aiwin_counter == 2 && player->getFrame() != 3) {
						player->animation("ko", 3, 100);
					}
					else if (player->getFrame() != 6 && aiwin_counter != 2) {
						player->animation("rounddefeat", 6, 100);
					}
					else {
						if (aiwin_counter == 2) {
							animation.texture = std::string(ASSET_PATH) + Playerfilename + "ko3.png";
						}
						else {
							animation.texture = std::string(ASSET_PATH) + Playerfilename + "rounddefeat6.png";
						}
						animation.outline_opacity = 0.0f;
						graphics::drawRect(player->getX(), player->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				else {
					if (aiwin_counter == 2 && player->getFrame() != 3) {
						player->animation("ko", 3, 100);
					}
					else if (player->getFrame() != 8 && aiwin_counter != 2) {
						player->animation("rounddefeat", 8, 100);
					}
					else
					{
						if (aiwin_counter == 2) {
							animation.texture = std::string(ASSET_PATH) + Playerfilename + "ko3.png";
						}
						else {
							animation.texture = std::string(ASSET_PATH) + Playerfilename + "rounddefeat8.png";
						}
						animation.outline_opacity = 0.0f;
						graphics::drawRect(player->getX(), player->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				graphics::setScale(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
				if (AIfilename == "bison\\") {
					if (ai->getFrame() != 4) {
						ai->animation("victory", 4, 100);
					}
					else {
						animation.texture = std::string(ASSET_PATH) + AIfilename + "victory4.png";
						animation.outline_opacity = 0.0f;
						graphics::drawRect(ai->getX(), ai->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				else {
					if (ai->getFrame() != 3) {
						ai->animation("victory", 3, 100);
					}
					else {
						animation.texture = std::string(ASSET_PATH) + AIfilename + "victory3.png";
						animation.outline_opacity = 0.0f;
						graphics::drawRect(ai->getX(), ai->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
			}
			else if (ai->getLife() == 0 && player->getLife() != 0) {
				graphics::setScale(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
				if (AIfilename == "bison\\") {
					if (playerwin_counter == 2 && ai->getFrame() != 3) {
						ai->animation("ko", 3, 100);
					}
					else if (ai->getFrame() != 6 && playerwin_counter != 2) {
						ai->animation("rounddefeat", 6, 100);
					}
					else {
						if (playerwin_counter == 2) {
							animation.texture = std::string(ASSET_PATH) + AIfilename + "ko3.png";
						}
						else {
							animation.texture = std::string(ASSET_PATH) + AIfilename + "rounddefeat6.png";
						}
						animation.outline_opacity = 0.0f;
						graphics::drawRect(ai->getX(), ai->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				else {
					if (playerwin_counter == 2 && ai->getFrame() != 3) {
						ai->animation("ko", 3, 100);
					}
					else if (ai->getFrame() != 8 && playerwin_counter != 2) {
						ai->animation("rounddefeat", 8, 100);
					}
					else {
						if (playerwin_counter == 2) {
							animation.texture = std::string(ASSET_PATH) + AIfilename + "ko3.png";
						}
						else {
							animation.texture = std::string(ASSET_PATH) + AIfilename + "rounddefeat8.png";
						}
						animation.outline_opacity = 0.0f;
						graphics::drawRect(ai->getX(), ai->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				graphics::setScale(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
				if (Playerfilename == "bison\\") {
					if (player->getFrame() != 4) {
						player->animation("victory", 4, 100);
					}
					else {
						animation.texture = std::string(ASSET_PATH) + Playerfilename + "victory4.png";
						animation.outline_opacity = 0.0f;
						graphics::drawRect(player->getX(), player->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
				else {
					if (player->getFrame() != 3) {
						player->animation("victory", 3, 100);
					}
					else {
						animation.texture = std::string(ASSET_PATH) + Playerfilename + "victory3.png";
						animation.outline_opacity = 0.0f;
						graphics::drawRect(player->getX(), player->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animation);
					}
				}
			}
			if (graphics::getGlobalTime() >= timeuntilgameend + 4000 && timeuntilgameend != 0) { // recognizes if is the game end 
				Application::getInstance().loaded = false;
				Menu* menu = new ChooseFighterMenu();
				Application::getInstance().setNewMenu(menu);
				Application::getInstance().setNewGame(nullptr);
			}
			else if (graphics::getGlobalTime() >= timeuntilroundwait + 4000 && timeuntilroundwait != 0) { // recognizes if is the round end
				ai->setLife();
				player->setLife();
				roundnumber++;
				timeuntilroundwait = 0;
				roundwait = true;
				timebetweenrounds = graphics::getGlobalTime();
			}
		}
		else if (!paused) {
			graphics::setScale(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			player->draw();
			graphics::setScale(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			ai->draw();
			pause.texture = std::string(ASSET_PATH) + "pause.png";
			pause.outline_opacity = 0.0f;
			graphics::drawRect(Application::getInstance().CanvasWidth - 50, Application::getInstance().CanvasHeight - 50, 100, 100, pause);
		}
		else if (paused) {
			player->drawLife();
			ai->drawLife();
			graphics::resetPose();
			graphics::setScale(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			graphics::drawRect(player->getX(), player->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, player->getAnimationBrush());
			graphics::setScale(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())), 1);
			graphics::drawRect(ai->getX(), ai->getY(), (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, ai->getAnimationBrush());
			graphics::resetPose();
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, 300, 500, pause);
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 100, 200, 45, option1);
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, 270, 45, option2);
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 + 100, 200, 45, option3);
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 + 200, 270, 45, option4);
			graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2 - 200, 240, 45, gamepaused);
		}
	}
	if (!Application::getInstance().loaded && graphics::getGlobalTime() <= loading + Application::getInstance().loadingtime) {
		loadingscreen.texture = std::string(ASSET_PATH) + "loading.png";
		loadingscreen.outline_opacity = 0.0f;
		roundwait = true;
		graphics::setScale(1, 1);
		graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight, loadingscreen);
	}
}

void Game::update()
{
	if (Application::getInstance().loaded && ai && player) { // update works if only the ai and player pointers exist and the fight is loaded
		graphics::getMouseState(mouse);
		if (!paused && !roundEnd() && !roundwait && (aiwin_counter != 2 && playerwin_counter != 2)) {
			player->update();
			AIactions();
			ai->update();
			if (ai->getX() - player->getX() >= -130 && ai->getX() - player->getX() <= 130) {
				CollisionDetector();
			}
		}
		if (mouse.button_left_pressed) { // this manages the pause option at the bottom right corner
			if (paused) { // if it is already paused then it manages the pause menu 
				// option for going back to start menu
				if (mouse.cur_pos_x >= Application::getInstance().CanvasWidth / 2 - 100 && mouse.cur_pos_x <= Application::getInstance().CanvasWidth / 2 + 100 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight / 2 - 100 + 22 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight / 2 - 100 - 22) {
					Menu* menu = new StartMenu();
					Application::getInstance().setNewMenu(menu);
					Application::getInstance().setNewGame(nullptr);
				}
				// option for going back to the choose fighter menu
				else if (mouse.cur_pos_x >= Application::getInstance().CanvasWidth / 2 - 135 && mouse.cur_pos_x <= Application::getInstance().CanvasWidth / 2 + 135 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight / 2 + 22 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight / 2 - 22) {
					Menu* menu = new ChooseFighterMenu();
					Application::getInstance().setNewMenu(menu);
					Application::getInstance().setNewGame(nullptr);

				}
				//option for going back to the choose map menu (the player's choice of fighter doesn't change)
				else if (mouse.cur_pos_x >= Application::getInstance().CanvasWidth / 2 - 100 && mouse.cur_pos_x <= Application::getInstance().CanvasWidth / 2 + 100 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight / 2 + 100 + 22 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight / 2 + 100 - 22) {
					Menu* menu = new ChooseMap();
					menu->fileanimation1 = Playerfilename;
					menu->fileanimation2 = AIfilename;
					Application::getInstance().setNewMenu(menu);
					Application::getInstance().setNewGame(nullptr);
				}
				// option for continuing the game
				else if (mouse.cur_pos_x >= Application::getInstance().CanvasWidth / 2 - 135 && mouse.cur_pos_x <= Application::getInstance().CanvasWidth / 2 + 135 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight / 2 + 200 + 22 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight / 2 + 200 - 22) {
					paused = false;
					pause.fill_opacity = 1.0f;
					pause.fill_color[0] = 1.0f;
					pause.fill_color[1] = 1.0f;
					pause.fill_color[2] = 1.0f;
					pause.outline_opacity = 0.0f;
				}
			}
			else {
				// this is the option of pausing the game while you are playing,you can also pause with SCANCODE_P 
				if (mouse.cur_pos_x >= Application::getInstance().CanvasWidth - 50 - 50 && mouse.cur_pos_x <= Application::getInstance().CanvasWidth - 50 + 50 && mouse.cur_pos_y <= Application::getInstance().CanvasHeight - 50 + 50 && mouse.cur_pos_y >= Application::getInstance().CanvasHeight - 50 - 50)
				{
					paused = true;
					pause.texture = "";
					pause.fill_opacity = 0.8f;
					pause.fill_color[0] = 0.2f;
					pause.fill_color[1] = 0.2f;
					pause.fill_color[2] = 0.2f;
					pause.outline_opacity = 1.0f;
					pause.outline_color[0] = 0.0f;
					pause.outline_color[1] = 0.0f;
					pause.outline_color[2] = 0.0f;
					option1.texture = std::string(ASSET_PATH) + "mainmenu.png";
					option1.outline_opacity = 0.0f;
					option2.texture = std::string(ASSET_PATH) + "choosefightermenu.png";
					option2.outline_opacity = 0.0f;
					option3.texture = std::string(ASSET_PATH) + "choosemapp.png";
					option3.outline_opacity = 0.0f;
					option4.texture = std::string(ASSET_PATH) + "continuegame.png";
					option4.outline_opacity = 0.0f;
					gamepaused.texture = std::string(ASSET_PATH) + "gamepaused.png";
					gamepaused.outline_opacity = 0.0f;
				}
			}
		}
		//continues the game with p
		else if (graphics::getKeyState(graphics::SCANCODE_P) && paused) {
			paused = false;
			pause.fill_opacity = 1.0f;
			pause.fill_color[0] = 1.0f;
			pause.fill_color[1] = 1.0f;
			pause.fill_color[2] = 1.0f;
			pause.outline_opacity = 0.0f;
		}
		// pauses the game with p
		else if (graphics::getKeyState(graphics::SCANCODE_P) && !paused)
		{
			paused = true;
			pause.texture = "";
			pause.fill_opacity = 0.8f;
			pause.fill_color[0] = 0.2f;
			pause.fill_color[1] = 0.2f;
			pause.fill_color[2] = 0.2f;
			pause.outline_opacity = 1.0f;
			pause.outline_color[0] = 0.0f;
			pause.outline_color[1] = 0.0f;
			pause.outline_color[2] = 0.0f;
			option1.texture = std::string(ASSET_PATH) + "mainmenu.png";
			option1.outline_opacity = 0.0f;
			option2.texture = std::string(ASSET_PATH) + "choosefightermenu.png";
			option2.outline_opacity = 0.0f;
			option3.texture = std::string(ASSET_PATH) + "choosemapp.png";
			option3.outline_opacity = 0.0f;
			option4.texture = std::string(ASSET_PATH) + "continuegame.png";
			option4.outline_opacity = 0.0f;
			gamepaused.texture = std::string(ASSET_PATH) + "gamepaused.png";
			gamepaused.outline_opacity = 0.0f;
		}
	}
}

void Game::adjustCanvas(int w, int h)
{
	Application::getInstance().CanvasWidth = w;
	Application::getInstance().CanvasHeight = h;
	if (ai && player && roundwait) { // we want the ai and the player to adjust their positions if only the round wait state is happening
		player->setX(Application::getInstance().CanvasWidth / 7);
		ai->setX(Application::getInstance().CanvasWidth / 7 * 6);
		player->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
		ai->setY(Application::getInstance().CanvasHeight / 7 * 4.7);
	}
}

Game::Game(std::string const& name, unsigned int const& frames, const std::string& filep, std::string const& fileai) { // the constructor of the game accepts 4 parameters: 1)name for the mapname,2)frames for the map frames,(3-4) file animation of player and ai
	player = new Player(filep);
	ai = new AI(fileai);
	Playerfilename = filep;
	AIfilename = fileai;
	mapname = name;
	mapframes = frames;
	loading = graphics::getGlobalTime();// this sets the loading time 
}

void Game::AIactions()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	// the values of the probalities are this low because ai actions method gets called multiple times
	/*These chances are used when the player is far from the AI*/
	std::bernoulli_distribution idle(0.02); // is used for true or false value to idle
	std::bernoulli_distribution walk(0.01); // is used for true or false chance to walk right
	std::bernoulli_distribution walkleftwhileclose(0.004);
	std::bernoulli_distribution walkrightwhileclose(0.004);
	std::bernoulli_distribution idlewhileclose(0.003);
	std::bernoulli_distribution jumpleftorright1(0.008); // is used for deciding to jump left with a certain chance
	std::bernoulli_distribution jumpleftorright2(0.003); // is used for deciding to jump left with a certain chance while player is moving towards ai's direction
	std::bernoulli_distribution walkwhileother(0.03); // is used for walking in the other direction while player is moving away from AI
	std::bernoulli_distribution idlewhilenotDorA(0.03); // random idle
	/*These chances are used when the player is in melee range*/
	std::bernoulli_distribution kick(0.003);
	std::bernoulli_distribution jumpattack(0.004);
	std::bernoulli_distribution attack(0.009);
	std::bernoulli_distribution crouch(0.003);
	std::bernoulli_distribution crouchattack(0.008);
	std::bernoulli_distribution jumprightorleftwhileclose(0.002);
	std::bernoulli_distribution crouchattackwhileplayerattacks(0.002);
	std::bernoulli_distribution block(0.03);
	/*pops melee or jump with a random chance*/
	std::bernoulli_distribution popMelee(0.05);
	std::bernoulli_distribution popJump(0.5);


	if (ai->getX() - player->getX() >= -130 && ai->getX() - player->getX() <= 130) {						//***************		MELEE RANGE		*******************
		// if the ai comes close and has active states from before then the stack must pop them
		if ((ai->getState() == EState::Idle || ai->getState() == EState::WalkLeft || ai->getState() == EState::WalkRight) && playerleftorright) {
			ai->pop();
			playerleftorright = false;
		}
		else if (ai->getState() == EState::JumpLeft || ai->getState() == EState::JumpRight && playerleftorright) {
			if (ai->getDuration() >= 500) {
				ai->pop();
				playerleftorright = false;
			}

		}
		// finish jump attack then start working with states and the ai must not be hit and the player must not be knocked down
		else if (ai->getState() != EState::JumpAttackUp && ai->getState() != EState::JumpAttackLeft && ai->getState() != EState::JumpAttackRight && !ai->getHit() && !player->getKnockdown()) { // wait until jump attack finishes 
			if (ai->getState() == EState::Block || ai->getState() == EState::Crouch || ai->getState() == EState::CrouchBlock) { // if block is happening then pop it with a certain time
				ai->popTime();
			}
			else if (ai->getState() == EState::Attack && ((duration >= 400 && AIfilename == "ken\\") || (duration >= 8 * 55 && AIfilename == "bison\\"))) { // if Attack state is happening pop it with a certain chance
				if (popMelee(gen)) {
					ai->pop();
				}
			}
			else if (ai->getState() == EState::Kick && ((duration >= 450 && AIfilename == "ken\\") || (duration >= 4 * 125 - 50 && AIfilename == "bison\\"))) {
				if (popMelee(gen)) {
					ai->pop();
				}
			}
			else if (ai->getState() == EState::CrouchAttack && ((duration >= 450 && AIfilename == "ken\\") || (duration >= 8 * 38 - 50 && AIfilename == "bison\\"))) {
				if (popMelee(gen)) {
					ai->pop();
				}
			}
			else if (ai->getState() == EState::Crouch) {
				if (crouchattack(gen) && player->getKeyState() == graphics::SCANCODE_C || (player->getKeyState() == graphics::SCANCODE_E && graphics::getKeyState(graphics::SCANCODE_C))) {
					ai->push(EState::CrouchAttack);
				}
				else
				{
					ai->popTime();
				}

			}
			else if ((player->getKeyState() == graphics::SCANCODE_C)|| (player->getKeyState() == graphics::SCANCODE_E && graphics::getKeyState(graphics::SCANCODE_C)) ) {
				if (crouchattack(gen)) {
					ai->push(EState::CrouchAttack);
				}
			}
			else if (player->getMouseState() == MouseI::LEFT_CLICK && !player->getHit()) {					//*********		If player attacks and is not hit
				if (block(gen)) {// if prob for block is true then block
					if (player->getKeyState() == graphics::SCANCODE_C || (player->getKeyState() == graphics::SCANCODE_E && graphics::getKeyState(graphics::SCANCODE_C)/*This is crouching while blocking and attacking with crouch*/)) {
						ai->push(EState::CrouchBlock);
					}
					else {
						ai->push(EState::Block);
					}
				}
				else if (crouchattackwhileplayerattacks(gen)) {
					ai->push(EState::CrouchAttack);
				}
			}
			else if (player->getMouseState() == MouseI::RIGHT_CLICK) { // if the player kicks either block or crouch or crouchattack
				if (block(gen)) {
					ai->push(EState::Block);
				}
				else if (crouch(gen)) {
					ai->push(EState::Crouch);
				}
				else if (crouchattackwhileplayerattacks(gen)) {
					ai->push(EState::CrouchAttack);
				}
			}
			if (!player->getHit() && player->getY() == ai->getY() && player->getKeyState() != graphics::SCANCODE_SPACE) {//if player is not jumping and the ai is not jumping aswell
				if (crouchattack(gen)) {
					ai->push(EState::CrouchAttack);
				}
				else if (attack(gen) && player->getKeyState() != graphics::SCANCODE_C && (player->getKeyState() != graphics::SCANCODE_E && !graphics::getKeyState(graphics::SCANCODE_C))) {
					ai->push(EState::Attack);
				}
				else if (kick(gen)) {
					ai->push(EState::Kick);
				}
			}
			else if (player->getKeyState() == graphics::SCANCODE_SPACE) { // if the player jumps
				if (jumpattack(gen))
				{
					if (graphics::getKeyState(graphics::SCANCODE_A)) {
						ai->push(EState::JumpAttackLeft);
					}
					else if (graphics::getKeyState(graphics::SCANCODE_D)) {
						ai->push(EState::JumpAttackRight);
					}
					else {
						ai->push(EState::JumpAttackUp);
					}
					ai->setDuration(0); // this start the jump attack from the start of the animation
				}
			}
			else {

				if (idlewhileclose(gen)) {

					ai->push(EState::Idle);
				}
				else if (walkleftwhileclose(gen)) {

					ai->push(EState::WalkLeft);
				}
				else if (walkrightwhileclose(gen)) {
					ai->push(EState::WalkRight);
				}

			}

		}
	}
	else if (ai->getX() - player->getX() > 130) {																//*******************		Makria o enas apo ton allon	(AI Dexia)	**************************
		if (!playerleftorright) {
			playerleftorright = true;
		}
		if (ai->getState() == EState::Crouch) {
			ai->pop();
		}
		else if (ai->getState() == EState::Attack) {
			if ((AIfilename == "ken\\" && ai->getDuration() >= 450) || (AIfilename == "bison\\" && ai->getDuration() >= 55 * 9 - 50)) {
				ai->pop();
			}
		}
		else if (ai->getState() == EState::CrouchAttack) {
			if ((AIfilename == "ken\\" && ai->getDuration() >= 250) || (AIfilename == "bison\\" && ai->getDuration() >= 8 * 38 - 50)) {
				ai->pop();
			}
		}
		else if (ai->getState() == EState::WalkRight && Application::getInstance().CanvasWidth - ai->getX() < 100) {											//*******		AN AI STON DEXIO TOIXO		********
			ai->pop();
		}
		else if (ai->getState() == EState::Idle || ai->getState() == EState::WalkRight) {
			ai->popTime();
		}
		else if (ai->getState() == EState::JumpLeft) {																											//*******	if	AI JUMP LEFT		********
			if (ai->getDuration() >= 500 && ai->getFrame() >= 6) {
				if (popJump(gen)) ai->pop();
			}
		}
		else {
			if (jumpleftorright1(gen) && (player->getKeyState() == graphics::SCANCODE_UNKNOWN || player->getKeyState() == graphics::SCANCODE_A)) {	//********	if	GEN_JUMPRIGHT	AND		PLAYER IDLE		OR		PLAYER WALKLEFT
				ai->push(EState::JumpLeft);
			}
			else if (jumpleftorright2(gen) && player->getKeyState() == graphics::SCANCODE_D) {	//********	if	GEN_JUMPRIGHT2		AND		PLAYER WALKRIGHT
				ai->push(EState::JumpLeft);
			}
			else if (idlewhilenotDorA(gen)) {				//			Random Idle for a while																										
				ai->push(EState::Idle);
			}
			else if (idle(gen) && player->getKeyState() == graphics::SCANCODE_D) {	//********  if	 GEN_IDLE		AND			PLAYER WALKRIGHT
				ai->push(EState::Idle);
			}
			else if (walk(gen) && ai->getState() != EState::Idle) {	//********  if   GEN_WALK		AND			AI NOT IDLE
				if (!Application::getInstance().CanvasWidth - ai->getX() < 100) {	//	if NOT AT RIGHT WALL
					ai->push(EState::WalkRight);
				}
				else {	//  if AT RIGHT WALL
					ai->push(EState::WalkLeft);
				}
			}
			else if (walkwhileother(gen) && ai->getState() != EState::Idle && player->getKeyState() == graphics::SCANCODE_D) {//*********	 if   GEN_WALK?		AND		PLAYER WALKRIGHT
				if (!Application::getInstance().CanvasWidth - ai->getX() < 100) {//	 if  AI NOT AT RIGHT WALL
					ai->push(EState::WalkRight);
				}
				else {//	 if  AI AT RIGHT WALL
					ai->push(EState::WalkLeft);
				}
			}
			else if (ai->getState() != EState::Idle && ai->getState() != EState::WalkRight) {//********** NONE OF THE ABOVE
				ai->push(EState::WalkLeft);
			}
		}
	}
	else if (ai->getX() - player->getX() < -130) {//***********			MAKRIA ( AI ARISTERA)		***************
		if (!playerleftorright) {
			playerleftorright = true;
		}
		if (ai->getState() == EState::Crouch) {
			ai->pop();
		}
		else if (ai->getState() == EState::Attack) {
			if ((AIfilename == "ken\\" && ai->getDuration() >= 450) || (AIfilename == "bison\\" && ai->getDuration() >= 55 * 9 - 50)) {
				ai->pop();
			}
		}
		else if (ai->getState() == EState::CrouchAttack) {
			if ((AIfilename == "ken\\" && ai->getDuration() >= 250) || (AIfilename == "bison\\" && ai->getDuration() >= 8 * 38 - 50)) {
				ai->pop();
			}
		}
		else if (ai->getState() == EState::WalkLeft && ai->getX() - 100 > -100) {
			ai->pop();
		}
		else if (ai->getState() == EState::Idle || ai->getState() == EState::WalkLeft) {
			ai->popTime();
		}
		else if (ai->getState() == EState::JumpRight) {
			if (ai->getDuration() >= 500 && ai->getFrame() >= 6) {
				if (popJump(gen)) ai->pop();
			}
		}
		else {
			if (jumpleftorright1(gen) && (player->getKeyState() == graphics::SCANCODE_UNKNOWN || player->getKeyState() == graphics::SCANCODE_D)) {
				ai->push(EState::JumpRight);
			}
			else if (jumpleftorright2(gen) && player->getKeyState() == graphics::SCANCODE_A) {
				ai->push(EState::JumpRight);
			}
			else if (idlewhilenotDorA(gen)) {//Random Idle for a while																										
				ai->push(EState::Idle);
			}
			else if (idle(gen) && player->getKeyState() == graphics::SCANCODE_A) {
				ai->push(EState::Idle);
			}
			else if (walk(gen) && ai->getState() != EState::Idle) {
				if (!Application::getInstance().CanvasWidth - ai->getX() < 100) {
					ai->push(EState::WalkLeft);
				}
				else {
					ai->push(EState::WalkRight);
				}
			}
			else if (walkwhileother(gen) && ai->getState() != EState::Idle && player->getKeyState() == graphics::SCANCODE_A) {
				if (!Application::getInstance().CanvasWidth - ai->getX() < 100) {
					ai->push(EState::WalkLeft);
				}
				else {
					ai->push(EState::WalkRight);
				}
			}
			else if (ai->getState() != EState::Idle && ai->getState() != EState::WalkLeft) {
				ai->push(EState::WalkRight);
			}
		}
	}
}

void Game::BackgroundAnimation(const std::string& name, unsigned const int& frames, unsigned const int& ms)
{
	frame = duration / ms + 1;
	if (frame > frames)
	{
		duration = 0;
		frame = 1;
	}
	map.texture = std::string(ASSET_PATH) + std::to_string(frame) + name;
	map.outline_opacity = 0.0f;
	graphics::drawRect(Application::getInstance().CanvasWidth / 2, Application::getInstance().CanvasHeight / 2, Application::getInstance().CanvasWidth, Application::getInstance().CanvasHeight, map);
	duration += graphics::getDeltaTime();
}




void Game::AssetWarmUp() { // asset warm up loads the assets of the animations before the game starts
	if (graphics::getGlobalTime() <= loading + 600) {
		ai->push(EState::Crouch);
		player->setKeyState(graphics::SCANCODE_C);
	}
	else if (graphics::getGlobalTime() <= loading + 1200) {
		if (ai->getState() == EState::Crouch) { ai->pop(); }
		ai->push(EState::Block);
		player->setKeyState(graphics::SCANCODE_E);
	}
	else if (graphics::getGlobalTime() <= loading + 2400) {
		ai->setHit(true);
		player->setHit(true);
	}
	else if (graphics::getGlobalTime() <= loading + 3900) {
		if (ai->getState() == EState::Block) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_UNKNOWN);
		ai->push(EState::Idle);
	}
	else if (graphics::getGlobalTime() <= loading + 5100) {
		if (ai->getState() == EState::Idle) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_D);
		ai->push(EState::WalkLeft);
	}
	else if (graphics::getGlobalTime() <= loading + 6900) {
		if (ai->getState() == EState::WalkLeft) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_SPACE);
		ai->push(EState::Jump);
	}
	else if (graphics::getGlobalTime() <= loading + 8400) {
		if (ai->getState() == EState::Jump) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_UNKNOWN);
		player->setMouseState(MouseI::LEFT_CLICK);
		ai->push(EState::Attack);
	}
	else if (graphics::getGlobalTime() <= loading + 9900) {
		if (ai->getState() == EState::Attack) { ai->pop(); }
		player->setMouseState(MouseI::RIGHT_CLICK);
		ai->push(EState::Kick);
	}
	else if (graphics::getGlobalTime() <= loading + 10800) {
		if (ai->getState() == EState::Kick) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_C);
		player->setMouseState(MouseI::LEFT_CLICK);
		ai->push(EState::CrouchAttack);
	}
	else if (graphics::getGlobalTime() <= loading + 11700) {
		if (ai->getState() == EState::CrouchAttack) { ai->pop(); }
		player->setKeyState(graphics::SCANCODE_SPACE);
		player->setMouseState(MouseI::LEFT_CLICK);
		ai->push(EState::JumpAttackUp);
	}
	else if (graphics::getGlobalTime() <= loading + 12600) {
		if (ai->getState() == EState::JumpAttackUp) { ai->pop(); }
		ai->animation("ko", 3, 100);
		player->animation("ko", 3, 100);
	}
	else if (graphics::getGlobalTime() <= loading + 13800) {
		if (AIfilename == "ken\\") {
			ai->animation("victory", 3, 100);
			player->animation("victory", 4, 100);
		}
		else
		{
			player->animation("victory", 3, 100);
			ai->animation("victory", 4, 100);
		}
	}
	else if (graphics::getGlobalTime() <= loading + 16200) {
		if (AIfilename == "ken\\") {
			ai->animation("rounddefeat", 8, 100);
			player->animation("rounddefeat", 5, 100);
		}
		else
		{
			player->animation("rounddefeat", 8, 100);
			ai->animation("roundefeat", 5, 100);
		}
	}
	else if (graphics::getGlobalTime() <= loading + 18600) {
		if (AIfilename == "ken\\") {
			ai->animation("knockdown", 8, 100);
			player->animation("knockdown", 5, 100);
		}
		else
		{
			player->animation("knockdown", 8, 100);
			ai->animation("knockdown", 5, 100);
		}
	}
}

bool Game::roundEnd()// round ends recognizes when a round has ended and when the game must end (ai win counter or player win counter == 2)
{
	// time until round wait initializes the waiting between rounds
	if (ai->getLife() == 0 || player->getLife() == 0) {
		if (AIfilename == "ken\\" && ai->getLife() == 0)
		{
			if (playerwin_counter == 0)
			{
				graphics::playSound(std::string(ASSET_PATH) + "bison_round.wav", 0.9f, false);
				timeuntilroundwait = graphics::getGlobalTime();
				playerwin_counter = 1;
			}
			else if (playerwin_counter == 1 && roundnumber - aiwin_counter - playerwin_counter > 0)
			{
				graphics::playSound(std::string(ASSET_PATH) + "You_won.wav", 1.0f, false);
				playerwin_counter = 2;
				timeuntilgameend = graphics::getGlobalTime();
			}
		}
		else if (AIfilename == "bison\\" && ai->getLife() == 0)
		{
			if (playerwin_counter == 0) {
				graphics::playSound(std::string(ASSET_PATH) + "Ryu_round.wav", 1.0f, false);
				timeuntilroundwait = graphics::getGlobalTime();
				playerwin_counter = 1;
			}
			else if (playerwin_counter == 1 && roundnumber - aiwin_counter - playerwin_counter > 0)
			{
				graphics::playSound(std::string(ASSET_PATH) + "You_won.wav", 1.0f, false);
				playerwin_counter = 2;
				timeuntilgameend = graphics::getGlobalTime();
			}
		}
		if (Playerfilename == "bison\\" && player->getLife() == 0) {
			if (aiwin_counter == 0) {
				graphics::playSound(std::string(ASSET_PATH) + "Ryu_round.wav", 0.9f, false);
				timeuntilroundwait = graphics::getGlobalTime();
				aiwin_counter = 1;
			}
			else if (aiwin_counter == 1 && roundnumber - aiwin_counter - playerwin_counter > 0) {
				aiwin_counter = 2;
				graphics::playSound(std::string(ASSET_PATH) + "youlost.wav", 1.0f, false);
				timeuntilgameend = graphics::getGlobalTime();
			}
		}
		else if (Playerfilename == "ken\\" && player->getLife() == 0) {
			if (aiwin_counter == 0) {
				graphics::playSound(std::string(ASSET_PATH) + "bison_round.wav", 0.9f, false);
				timeuntilroundwait = graphics::getGlobalTime();
				aiwin_counter = 1;
			}
			else if (aiwin_counter == 1 && roundnumber - aiwin_counter - playerwin_counter > 0) {
				graphics::playSound(std::string(ASSET_PATH) + "youlost.wav", 1.0f, false);
				aiwin_counter = 2;
				timeuntilgameend = graphics::getGlobalTime();
			}
		}

		countdown_num = 4;
		return true;
	}
	return false;
}

void Game::CollisionDetector() { // collision detector manages all the collisions 
	//setHit(true) method is used for sending information to the ai or the player class to do the facehit animation
	//setKnockdown again sends information to the player and ai class to do the knockdown animation and change x and y accordingly
	//setAttackflag along with setDuration ensures that the animation of facehit and knockdown only happen once and drainlife method doesn't repeatedly call it self through update
	//THE PLAYER IS ATTACKING THE AI
	if (!ai->getHit() && !ai->getKnockdown() && ai->getState() != EState::Block && ai->getState() != EState::CrouchBlock) {
		if (player->getY() == ai->getY() && (player->getKeyState() != graphics::SCANCODE_SPACE && (ai->getState() != EState::JumpLeft && ai->getState() != EState::JumpRight && ai->getState() != EState::Jump))) {
			if (((player->getDuration() >= 220 && player->getDuration() <= 275 && Playerfilename == "bison\\") || (player->getDuration() >= 300 && player->getDuration() <= 350 && Playerfilename == "ken\\")) && player->getMouseState() == MouseI::LEFT_CLICK && player->getAttackflag()) {
				if (ai->getState() != EState::Crouch) {
					ai->setHit(true);
					ai->setDuration(0);
					ai->drainLife(0.04f);
					player->setAttackflag(false);
				}
			}
			else if (((player->getDuration() >= 375 && player->getDuration() <= 450 && Playerfilename == "bison\\") || (player->getDuration() >= 300 && player->getDuration() <= 350 && Playerfilename == "ken\\")) && player->getMouseState() == MouseI::RIGHT_CLICK && player->getAttackflag())
			{
				if (ai->getState() != EState::Crouch) {
					ai->setHit(true);
					ai->setDuration(0);
					ai->drainLife(0.03f);
					player->setAttackflag(false);
				}
			}
			else if (((player->getDuration() >= 190 && player->getDuration() <= 228 && Playerfilename == "bison\\") || (player->getDuration() >= 200 && player->getDuration() <= 300 && Playerfilename == "ken\\")) && player->getMouseState() == MouseI::LEFT_CLICK && player->getKeyState() == graphics::SCANCODE_C && player->getAttackflag()) {
				ai->setHit(true);
				ai->setDuration(0);
				ai->drainLife(0.03f);
				player->setAttackflag(false);
			}
		}
		else {
			if (player->getMouseState() == MouseI::LEFT_CLICK && player->getAttackflag()) {
				if (player->getKeyState() == graphics::SCANCODE_SPACE && (ai->getState() == EState::JumpLeft || ai->getState() == EState::JumpRight || ai->getState() == EState::Jump || ai->getState() == EState::JumpAttackLeft || ai->getState() == EState::JumpAttackRight || ai->getState() == EState::JumpAttackUp)) {
					if ((player->getDuration() >= 210 && player->getDuration() <= 280 && Playerfilename == "bison\\") || (player->getDuration() >= 200 && player->getDuration() <= 250 && Playerfilename == "ken\\")) {
						ai->setKnockdown(true);
						ai->setknockdownXdirection(1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())));
						ai->setDuration(0);
						ai->drainLife(0.06);
						player->setAttackflag(false);
					}
				}
			}
		}
	}
	else if ((ai->getState() == EState::Block || ai->getState() == EState::CrouchBlock) && player->getKeyState() != graphics::SCANCODE_SPACE && !ai->getHit()) {
		if ((player->getMouseState() == MouseI::LEFT_CLICK || player->getMouseState() == MouseI::RIGHT_CLICK) && player->getAttackflag()) {
			if (((player->getDuration() >= 190 && player->getDuration() <= 228 && Playerfilename == "bison\\") || (player->getDuration() >= 200 && player->getDuration() <= 300 && Playerfilename == "ken\\")) && (player->getKeyState() == graphics::SCANCODE_C || (player->getKeyState() == graphics::SCANCODE_E && graphics::getKeyState(graphics::SCANCODE_C)))) {
				if (ai->getState() == EState::CrouchBlock && player->getMouseState() != MouseI::RIGHT_CLICK) {
					ai->drainLife(0.01f);
					ai->changePosX(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())) * 10);
					player->setAttackflag(false);
				}
				else {
					if (player->getMouseState() != MouseI::RIGHT_CLICK) {
						ai->setHit(true);
						ai->setDuration(0);
						ai->drainLife(0.03f);
						player->setAttackflag(false);
					}
				}
			}
			else if (((player->getDuration() >= 220 && player->getDuration() <= 275 && Playerfilename == "bison\\") || (player->getDuration() >= 300 && player->getDuration() <= 400 && Playerfilename == "ken\\"))) {
				if (ai->getState() == EState::Block) {
					ai->drainLife(0.01f);
					ai->changePosX(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())) * 10);
					player->setAttackflag(false);
				}
			}
		}
	}

	//drainLife(0.04f) -> For normal attacks while not blocked
	//drainLife(0.06) ->  For knockdown attacks while jumped
	//drainLife(0.01f) -> For all the attacks while blocked
	//drainLife(0.03f) -> For all the crouchattacks while not blocked

	//**************************************************************				AI ATTACKING PLAYER				**************************************************************


	if (player->getY() == ai->getY() && player->getKeyState() != graphics::SCANCODE_SPACE) {
		if ((ai->getState() == EState::Attack || ai->getState() == EState::Kick) && !player->getHit() && ai->getAttackflag()) {					// AI ATTACK OR KICK	
			if (player->getKeyState() != graphics::SCANCODE_E) {				//PLAYER NOT BLOCK NOT CROUCHBLOCK
				if (player->getKeyState() != graphics::SCANCODE_C) {					//PLAYER NOT CROUCH
					if (ai->getState() == EState::Attack					/*AI PUNCH*/ && ((ai->getDuration() >= 400 && ai->getDuration() <= 450 && AIfilename == "bison\\") || (ai->getDuration() >= 300 && ai->getDuration() <= 350 && AIfilename == "ken\\"))) {
						player->setHit(true);
						player->setDuration(0);
						player->drainLife(0.04f);
						ai->setAttackflag(false);
					}
					else if (ai->getState() == EState::Kick					/*AI KICK*/ && ((ai->getDuration() >= 3 * 125 && ai->getDuration() <= 4 * 125 && AIfilename == "bison\\") || (ai->getDuration() >= 300 && ai->getDuration() <= 350 && AIfilename == "ken\\"))) {
						player->setHit(true);
						player->setDuration(0);
						player->drainLife(0.04f);
						ai->setAttackflag(false);
					}
				}
			}
			else if (											/*PLAYER BLOCK OR CROUCHBLOCK*/							((ai->getDuration() >= 400 && ai->getDuration() <= 450 || ai->getDuration() >= 3 * 125 && ai->getDuration() <= 4 * 125) && AIfilename == "bison\\") || (ai->getDuration() >= 300 && ai->getDuration() <= 350 && AIfilename == "ken\\")) {
				player->drainLife(0.01f);
				player->changePosX((1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX()))) * 10);
				ai->setAttackflag(false);
			}
		}


		else if (ai->getState() == EState::CrouchAttack && !player->getHit() && ai->getAttackflag()) {			//AI CROUCH ATTACK 
			if (player->getKeyState() == graphics::SCANCODE_E && graphics::getKeyState(graphics::SCANCODE_C)		/*PLAYER CROUCHBLOCK*/ && ((ai->getDuration() >= 5 * 38 && ai->getDuration() <= 6 * 38 && AIfilename == "bison\\") || (ai->getDuration() >= 200 && ai->getDuration() <= 230 && AIfilename == "ken\\"))) {
				player->drainLife(0.01f);
				player->setDuration(0);
				player->changePosX((1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX()))) * 10);
				ai->setAttackflag(false);
			}
			else if (((ai->getDuration() >= 5 * 38 && ai->getDuration() <= 6 * 38 && AIfilename == "bison\\") || (ai->getDuration() >= 200 && ai->getDuration() <= 230 && AIfilename == "ken\\"))) {																									/* PLAYER NOT CROUCHBLOCK*/
				player->setHit(true);
				player->setDuration(0);
				player->drainLife(0.04f);
				ai->setAttackflag(false);
			}
		}
	}
	else if ((ai->getState() == EState::JumpAttackLeft || ai->getState() == EState::JumpAttackRight || ai->getState() == EState::JumpAttackUp) && ai->getAttackflag() && !player->getKnockdown()) {		/*AI JUMP ATTACK*/
		if (player->getKeyState() == graphics::SCANCODE_SPACE/*PLAYER JUMP*/ && ((ai->getDuration() >= 200 && ai->getDuration() <= 250 && AIfilename == "ken\\") || (ai->getDuration() >= 210 && ai->getDuration() <= 280 && AIfilename == "bison\\"))) {
			player->setKnockdown(true);
			player->setknockdownXdirection(-1 * (ai->getX() - player->getX()) / (std::abs(ai->getX() - player->getX())));
			player->setDuration(0);
			player->drainLife(0.06f);
			ai->setAttackflag(false);
		}

	}
}
Game::~Game()
{
	delete player;
	delete ai;
}