#include <iostream>
#include <cmath>
#include "Vector3.hpp"
using namespace std;
Vector3 Vector3::operator +(const Vector3 & v)
{
    return Vector3(x + v.x,
                    y + v.y,
                    z + v.z);
}

Vector3 Vector3::operator -(const Vector3 &v)
{
    return Vector3(x - v.x,
                    y - v.y,
                    z - v.z);
}

float Vector3::operator*(const Vector3 &v)//vector dot multiply
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator ^(const Vector3 &v)//vector cross multiply
{
    return Vector3(y * v.z - z * v.y,
                    z * v.x - x * v.z,
                    x * v.y - y * v.x);
}

bool Vector3::operator ==(const Vector3 &v)
{
    return x == v.x && y == v.y && z == v.z;
}

void Vector3::out()
{
    cout << '(' << x << ',' << y << ',' << z << ')' << endl;
}

Vector3 &Vector3::normalize()
{
    float temp = sqrt(x * x + y * y + z * z);
    x /= temp;
    y /= temp;
    z /= temp;
    return *this;
}

float Vector3::Lenth()
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 &Vector3::copy(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vector3 Vector3::multiply(float n)
{
	return Vector3(x*n, y*n, z*n);
}

float Vector3::sqrLenth()
{
    return x * x + y * y + z * z;
}

Vector3 &Vector3::operator=(const Vector3 &v)
{
	return this->copy(v);
}

Vector3 Vector3::operator/(float n)
{
	return Vector3(x / n, y / n, z / n);
}