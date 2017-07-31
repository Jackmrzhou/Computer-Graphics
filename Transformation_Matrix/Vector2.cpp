#include "Vector2.hpp"
#include <cmath>
using namespace std;

float Vector2::operator*(const Vector2 &v)
{
	return x*v.x + y*v.y;
}

Vector2 Vector2::operator+(const Vector2 &v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v)
{
	return Vector2(x - v.x, y - v.y);
}
