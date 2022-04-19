#pragma once
#include "Application.h"
#include "MathVector.h"
class Fighter // abstract class that has the shared methods and variables for player and ai which are both children of fighter
{
protected:
	float pos_x = 0;
	float pos_y = 0;
	short scaledirection = 0;
	unsigned int jumpduration = 0;
	MathVector velocity; // MathVector is a vector class that helps create the feel of gravity and acceleration and velocity in the game
	MathVector grav;
	graphics::Brush animationbr;
	graphics::Brush br_life;
	float duration = 0;
	unsigned short frame = 1;
	float speed = 10.0f;
	graphics::MouseState mouse;
	std::string file_animation;
	float life = 1;
	bool attackflag,facehit,knockdown,endjumpattack = false;
	short knockdownxdirection = 1;
public:
	void virtual draw() = 0;
	void virtual update() = 0;
	void virtual animation(const std::string& name, unsigned const int& frames, unsigned const int& ms) = 0;
	float getX() const;
	float getY() const;
	void drawLife();
	void drainLife(const float amount);
	float getLife() const;
	float getDuration() const;
	void setDuration(short x);
	void setLife();
	unsigned int getFrame() const;
	graphics::Brush getAnimationBrush() const;
	void changePosX(float value);
	void setX(float value);
	void setY(float value);
	void setHit(bool value);
	bool getHit() const;
	void setKnockdown(bool value);
	bool getKnockdown() const;
	bool getAttackflag() const;
	void setAttackflag(bool value);
	void setknockdownXdirection(short x);
};
