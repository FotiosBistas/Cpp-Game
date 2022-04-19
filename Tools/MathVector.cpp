#include "MathVector.h"

void MathVector::setAngle(float angle) 
{
    float length = getLength();
    x = (cos(angle) * length);
    y = (sin(angle) * length);
}

float MathVector::getLength() const
{
    return sqrt(x * x + y * y);
}

MathVector MathVector::operator*(float value)
{
    MathVector new_vec(this->x * value, this->y * value);
    return new_vec;
}

MathVector MathVector::operator+(const MathVector& vec)
{
    MathVector new_vec(this->x + vec.getX(), this->y + vec.getY());
    return new_vec;
}

MathVector MathVector::operator*(const MathVector& vec) {
    MathVector new_vec(this->x * vec.getX(), this->y * vec.getY());
    return new_vec;
}


void MathVector::setX(float value) {
    x = value;
}

MathVector MathVector::operator-(const MathVector& vec)
{
    MathVector new_vec(this->x - vec.getX(), this->y - vec.getY());
    return new_vec;
}

void MathVector::setY(float value) {
    y = value;
}

float MathVector::getX() const
{
    return x;
}

 void MathVector::setLength(float length)
{
    float angle = getAngle();
    x = cos(angle) * length;
    y = sin(angle) * length;
}

float MathVector::getY() const
{
    return y;
}

float MathVector::getAngle() const
{
    return atan2(y,x);
}
