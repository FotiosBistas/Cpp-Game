#pragma once
#include "Application.h"
#include <cmath>

class MathVector
{
	float x = 0;
	float y = 0;
public:
	MathVector() {};
	MathVector(float x, float y) :x(x), y(y) {}
	void setAngle(float angle);
	float getLength() const;
	MathVector operator+(const MathVector& vec);
	MathVector operator-(const MathVector& vec);
	MathVector operator*(const MathVector& vec);
	MathVector operator*(float value);
	void setX(float value);
	void setY(float value);
	void setLength(float length);
	float getX() const;
	float getY() const;
	float getAngle() const;
};

