#pragma once
#ifndef _VECTOR2_H
#define _VECTOR2_H
class Vector2
{
public:
	Vector2() { x = y = 0; }
	Vector2(float a, float b)
	{
		x = a, y = b;
	}
	float x, y;
	Vector2 operator+(const Vector2 &v);
	float operator*(const Vector2 &v);
	Vector2 operator-(const Vector2 &v);
};
#endif // !_VECTOR2_H