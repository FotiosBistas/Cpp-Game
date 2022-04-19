#include "AI.h"
void AI::animation(const std::string& name, unsigned const int& frames, unsigned const int& ms) {
	if (duration < ms * frames || duration / ms + 1 <= frames)
	{
		if (currentState != getState() && name != "facehit" && name != "knockdown") { // if the state changes it means that the animation must start from its first frame
			duration = 0;
			currentState = getState();
		}
		if (name == "jump") { // this is used for the air attacks the explanation is the else the first if(end of animation)
			duration = jumpduration;
		}
		frame = duration / ms + 1;
		animationbr.texture = std::string(ASSET_PATH) + file_animation + name + std::to_string(frame) + ".png";
		if (duration == 0 && Application::getInstance().loaded)
		{
			graphics::playSound(std::string(ASSET_PATH) + name + ".wav", 0.5f);

			if (name == "attack" || name == "jumpattack" || name == "kick" || name == "jumpkick" || name == "crouchkick" || name == "crouchattack")
			{
				attackflag = true;
			}
		}
		animationbr.outline_opacity = 0.0f;
		graphics::drawRect(pos_x, pos_y, (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animationbr);
		duration += graphics::getDeltaTime();
		if (name == "jump") {
			jumpduration += graphics::getDeltaTime();
		}
	}
	else
	{
		/*if (name == "jumpkick" || name == "jumpattack") {// this continues the jump animation if a jump attack finishes in the air
			jumpduration += duration;
			pop();
		}*/
		duration = 0;
		if (facehit) {
			facehit = false;
		}
		if (knockdown) {
			knockdown = false;
		}
	}
}

//stack methods
EState AI::pop()
{
	return brain->popState();
}

EState AI::popTime()
{
	return brain->popStateWithTime();
}

AI::~AI()
{
	delete brain;
}

EState AI::getState() const
{
	return brain->getCurrentState();
}

void AI::push(const EState state)
{
	brain->pushState(state);
}
void AI::clear() {
	brain->clearStack();
}
AI::AI(const std::string& file)
{
	pos_x = Application::getInstance().CanvasWidth / 7 * 6;
	pos_y = Application::getInstance().CanvasHeight / 7 * 4.7;
	brain = new StackFSM(10);
	scaledirection = -1;
	file_animation = file;
	push(EState::Idle);
	velocity = MathVector(2, 2);
	grav = MathVector(0, -2);
	currentState = getState(); //  the active state of the finite machine which works with enums
}

void AI::draw()
{
	if (facehit) {

		if (file_animation == "ken\\") {
			animation("facehit", 4, 100);
		}
		else {
			animation("facehit", 3, 133);
		}

	}
	else if (knockdown) {
		if (file_animation == "ken\\") {
			animation("knockdown", 8, 150);
		}
		else {
			animation("knockdown", 5, 240);
		}
	}
	else {
		switch (getState()) {
		case EState::Idle:
			if (file_animation == "ken\\") {
				animation("idle", 4, 100);
			}
			else {
				animation("idle", 4, 100);
			}
			break;
		case EState::WalkLeft:
			if (file_animation == "ken\\") {
				animation("walk", 5, 100);
			}
			else {
				animation("walk", 4, 100);
			}
			break;
		case EState::WalkRight:
			if (file_animation == "ken\\") {
				animation("walk", 5, 100);
			}
			else {
				animation("walk", 4, 100);
			}
			break;
		case EState::Jump:
			if (file_animation == "ken\\") {
				animation("jump", 6, 100);
			}
			else {
				animation("jump", 6, 100);
			}
			break;
		case EState::Attack:
			if (file_animation == "ken\\") {
				animation("attack", 5, 100);
			}
			else {
				animation("attack", 9, 55);
			}
			break;
		case EState::Kick:
			if (file_animation == "ken\\") {
				animation("kick", 5, 100);
			}
			else {
				animation("kick", 4, 125);
			}
			break;
		case EState::CrouchBlock:
			animationbr.texture = std::string(ASSET_PATH) + file_animation + "block" + std::to_string(2) + ".png";
			animationbr.outline_opacity = 0.0f;
			graphics::drawRect(pos_x, pos_y, (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animationbr);
			break;
		case EState::Block:
			animationbr.texture = std::string(ASSET_PATH) + file_animation + "block" + std::to_string(1) + ".png";
			animationbr.outline_opacity = 0.0f;
			graphics::drawRect(pos_x, pos_y, (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animationbr);
			break;
		case EState::Crouch:
			animationbr.texture = std::string(ASSET_PATH) + file_animation + "crouch" + std::to_string(2) + ".png";
			animationbr.outline_opacity = 0.0f;
			graphics::drawRect(pos_x, pos_y, (Application::getInstance().CanvasWidth / 1280) * (float)1182 / 2.7, (Application::getInstance().CanvasHeight / 720) * (float)600 / 2.7, animationbr);
			break;
		case EState::JumpLeft:
			if (file_animation == "ken\\") {
				animation("jump", 6, 100);
			}
			else {
				animation("jump", 6, 100);
			}
			break;
		case EState::JumpRight:
			if (file_animation == "ken\\") {
				animation("jump", 6, 100);
			}
			else {
				animation("jump", 6, 100);
			}
			break;
		case EState::JumpAttackLeft:
			if (file_animation == "ken\\") {
				animation("jumpkick", 3, 100);
			}
			else {
				animation("jumpattack", 6, 100);
			}
			break;
		case EState::JumpAttackRight:
			if (file_animation == "ken\\") {
				animation("jumpkick", 3, 100);
			}
			else {
				animation("jumpattack", 6, 100);
			}
			break;
		case EState::JumpAttackUp:
			if (file_animation == "ken\\") {
				animation("jumpkick", 3, 100);
			}
			else {
				animation("jumpattack", 6, 100);
			}
			break;
		case EState::CrouchAttack:
			if (file_animation == "ken\\") {
				animation("crouchkick", 3, 100);
			}
			else {
				animation("crouchattack", 8, 38);
			}
			break;
		}
	}
	drawLife();
}

void AI::update()
{
	if (knockdown) {
		if (pos_y <= Application::getInstance().CanvasHeight / 7 * 4.7) {
			pos_y = pos_y - velocity.getY() * graphics::getDeltaTime() / 1.7;
			velocity = velocity + grav * (graphics::getDeltaTime() / 150);
		}
		if (pos_x > Application::getInstance().CanvasWidth / 7 * 0.5 && pos_x < Application::getInstance().CanvasWidth / 7 * 6.5) {
			if (duration <= 450 && file_animation == "ken\\") {
				velocity.setX(0.8 - 0.8 * (duration) / (3 * 150));
				pos_x = pos_x + (knockdownxdirection)*velocity.getX() * graphics::getDeltaTime() / 2;
			}

			else if (file_animation == "bison\\" && frame <= 2) {
				velocity.setX(2 - 2 * (duration) / (2 * 240));
				pos_x = pos_x + (knockdownxdirection)*velocity.getX() * graphics::getDeltaTime() / 2;
			}

		}
		else
		{
			velocity.setX(0);
			if (pos_x <= Application::getInstance().CanvasWidth / 7 * 0.5) {
				pos_x = Application::getInstance().CanvasWidth / 7 * 0.5;
			}
			else {
				pos_x = Application::getInstance().CanvasWidth / 7 * 6.5;
			}
		}

	}

	
	if (!facehit && !knockdown) {
		if (getState() == EState::Jump || getState() == EState::JumpLeft || getState() == EState::JumpRight || getState() == EState::JumpAttackUp || getState() == EState::JumpAttackLeft || getState() == EState::JumpAttackRight) {
			if (file_animation == "ken\\") {
				if (pos_y - velocity.getY() * graphics::getDeltaTime() / 1.7 > Application::getInstance().CanvasHeight / 7 * 4.7) {
					velocity = MathVector(1, 2);
					jumpduration = 0;
				}
				else {
					pos_y = pos_y - velocity.getY() * graphics::getDeltaTime() / 1.7;
					velocity = velocity + grav * (graphics::getDeltaTime() / 300);
				}
			}
			else {
				if (pos_y - velocity.getY() * graphics::getDeltaTime() / 1.7 > Application::getInstance().CanvasHeight / 7 * 4.7) {
					velocity = MathVector(1, 2);
					jumpduration = 0;
				}
				else {
					pos_y = pos_y - velocity.getY() * graphics::getDeltaTime() / 1.7;
					velocity = velocity + grav * (graphics::getDeltaTime() / 300);
				}
			}
			if (getState() == EState::JumpLeft || getState() == EState::JumpAttackLeft) {


				if (pos_x > Application::getInstance().CanvasWidth / 7 * 0.5) {
					velocity.setX(0.8);
					pos_x = pos_x - velocity.getX() * graphics::getDeltaTime() / 1.7;

				}
				else
				{
					velocity.setX(0);
					pos_x = Application::getInstance().CanvasWidth / 7 * 0.5;
				}

			}
			else if (getState() == EState::JumpRight || getState() == EState::JumpAttackRight) {

				if (pos_x < Application::getInstance().CanvasWidth / 7 * 6.5) {
					velocity.setX(0.8);
					pos_x = pos_x + velocity.getX() * graphics::getDeltaTime() / 1.7;

				}
				else
				{
					velocity.setX(0);
					pos_x = Application::getInstance().CanvasWidth / 7 * 6.5;
				}
			}
		}
		else
		{
			pos_y = Application::getInstance().CanvasHeight / 7 * 4.7;
		}
		if (getState() == EState::WalkLeft) {
			if (pos_x > Application::getInstance().CanvasWidth / 7 * 0.5) {
				velocity.setX(0.8);
				pos_x = pos_x - velocity.getX() * graphics::getDeltaTime() / 1.7;

			}
			else
			{
				velocity.setX(0);
				pos_x = Application::getInstance().CanvasWidth / 7 * 0.5;
			}
		}

		if (getState() == EState::WalkRight) {
			if (pos_x < Application::getInstance().CanvasWidth / 7 * 6.5) {
				velocity.setX(0.8);
				pos_x = pos_x + velocity.getX() * graphics::getDeltaTime() / 1.7;

			}
			else
			{
				velocity.setX(0);
				pos_x = Application::getInstance().CanvasWidth / 7 * 6.5;
			}
		}
	}


}

