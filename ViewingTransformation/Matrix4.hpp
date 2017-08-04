#pragma once
#ifndef _Matrix_H
#define _Matrix_H
#include "Vector3.hpp"
class Matrix4
{
public:
	Matrix4();
	Matrix4(const Matrix4 &m);
	Matrix4(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4);
	float data[4][4];
	//always assume the last row is 0,0,0,1
	Matrix4 operator*(const Matrix4 &m);
	Vector3 operator*(const Vector3 &v);
};

#endif // !_Matrix_H
