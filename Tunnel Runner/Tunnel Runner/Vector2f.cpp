#include "Vector2f.h"


Vector2f::Vector2f(float X, float Y):x(X),y(Y)
{
}

Vector2f::Vector2f():x(0),y(0)
{
}

Vector2f::~Vector2f(void)
{
}

float Vector2f::length()
{
	return sqrt((x*x)+(y*y));
}

Vector2f Vector2f::operator/(float f)
{
	return Vector2f(x/f,y/f);
}

Vector2f Vector2f::operator*(float f)
{
	return Vector2f(x*f,y*f);
}

void Vector2f::operator*=(float f)
{
	x*=f;
	y*=f;
}

void Vector2f::operator/=(float f)
{
	x/=f;
	y/=f;
}

Vector2f Vector2f::operator+(Vector2f f)
{
	return Vector2f(x+f.x,y+f.y);
}

Vector2f Vector2f::operator-(Vector2f f)
{
	return Vector2f(x+(-f.x),y+(-f.y));
}

void Vector2f::operator+=(Vector2f f)
{
	x+=f.x;
	y+=f.y;
}

void Vector2f::operator-=(Vector2f f)
{
	x+=(-f.x);
	y+=(-f.y);
}