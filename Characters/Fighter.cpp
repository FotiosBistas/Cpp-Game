#include "Fighter.h"
float Fighter::getX() const {
	return pos_x;
}

float Fighter::getY() const {
	return pos_y;
}
void Fighter::drawLife() {
	graphics::setScale(scaledirection,1);
	br_life.outline_opacity = 1.0f;
	br_life.outline_color[0] = 0.0f;
	br_life.outline_color[1] = 0.0f;
	br_life.outline_color[2] = 0.0f;
	br_life.fill_color[0] = 1.0f;
	br_life.fill_color[1] = 0.3f;
	br_life.fill_color[2] = 0.3f;
	br_life.fill_secondary_color[0] = 0.8f;
	br_life.fill_secondary_color[1] = 1.0f;
	br_life.fill_secondary_color[2] = 0.0f;
	br_life.gradient = true;
	br_life.gradient_dir_u = 1.0f;
	br_life.gradient_dir_v = 0.0f;
	br_life.texture = "";
	if (scaledirection == -1) {
		graphics::drawRect((Application::getInstance().CanvasWidth - 100) - (life * 500) / 2, 80, life * 500, 50, br_life);
	}
	else {
		graphics::drawRect(100 + (life * 500) / 2, 80, life * 500, 50, br_life);
	}
	br_life.gradient = false;
	br_life.fill_opacity = 0.3f;
	br_life.texture = "";
	if (scaledirection == -1) {
		graphics::drawRect(Application::getInstance().CanvasWidth - 350, 80, 500, 50, br_life);
	}
	else {
		graphics::drawRect(350, 80, 500, 50, br_life);
	}
	br_life.outline_opacity = 0.0f;
	br_life.outline_color[0] = 1.0f;
	br_life.outline_color[1] = 1.0f;
	br_life.outline_color[2] = 1.0f;
	br_life.fill_color[1] = 1.0f;
	br_life.fill_color[2] = 1.0f;
	br_life.fill_secondary_color[0] = 1.0f;
	br_life.fill_secondary_color[2] = 1.0f;
	br_life.fill_opacity = 1.0f;
	br_life.texture = std::string(ASSET_PATH) + file_animation + "mugshot.png";
	br_life.outline_opacity = 0.0f;
	if (scaledirection == -1) {
		graphics::drawRect(Application::getInstance().CanvasWidth - 50, 55, 100, 100, br_life);
	}
	else {
		graphics::drawRect(50, 55, 100, 100, br_life);
	}
}

void Fighter::drainLife(const float amount) {
	life = std::max<float>(0.0f, life - amount);
	if (amount == 0.04f && duration == 0)
	{
		graphics::playSound(std::string(ASSET_PATH) + "punch.wav", 0.5f);
	}
	else if (amount == 0.01f && duration == 0)
	{
		graphics::playSound(std::string(ASSET_PATH) + "attack_block.wav", 0.5f);
	}
}

float Fighter::getLife() const {
	return life;
}

float Fighter::getDuration() const
{
	return duration;
}

void Fighter::setDuration(short x)
{
	duration = x;
}

void Fighter::setLife() {
	life = 1;
}

unsigned int Fighter::getFrame() const {
	return frame;
}

graphics::Brush Fighter::getAnimationBrush() const {
	return animationbr;
}

void Fighter::changePosX(float value) {
	if (pos_x > Application::getInstance().CanvasWidth / 7 * 0.5 && pos_x < Application::getInstance().CanvasWidth / 7 * 6.5) {
		pos_x = pos_x - value;
	}
	else {
		if (pos_x <= Application::getInstance().CanvasWidth / 7 * 0.5) {
			pos_x = Application::getInstance().CanvasWidth / 7 * 0.5;
		}
		else if (pos_x >= Application::getInstance().CanvasWidth / 7 * 6.5) {
			pos_x = Application::getInstance().CanvasWidth / 7 * 6.5;
		}
	}
}

void Fighter::setX(float value) {
	pos_x = value;
}

void Fighter::setY(float value) {
	pos_y = value;
}

bool Fighter::getAttackflag() const
{
	return attackflag;
}

void Fighter::setHit(bool value)
{
	facehit = value;
}

bool Fighter::getHit() const {	
	return facehit;
}

void Fighter::setAttackflag(bool value) {
	attackflag = value;
}

void Fighter::setknockdownXdirection(short x) {
	knockdownxdirection = x;
}

void Fighter::setKnockdown(bool value)
{
	knockdown = value;
}

bool Fighter::getKnockdown() const
{
	return knockdown;
}
