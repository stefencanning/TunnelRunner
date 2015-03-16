#pragma once
#ifndef VECTOR2F_H
#define VECTOR2F_H
#include <math.h>
class Vector2f
{
public:
	Vector2f(float x, float y);
	Vector2f();
	~Vector2f(void);
	float length();
	float x;
	float y;
	Vector2f operator/(float f);
	Vector2f operator*(float f);
	void operator*=(float f);
	void operator/=(float f);
	Vector2f operator+(Vector2f v);
	Vector2f operator-(Vector2f v);
	void operator+=(Vector2f v);
	void operator-=(Vector2f v);
};
#endif

