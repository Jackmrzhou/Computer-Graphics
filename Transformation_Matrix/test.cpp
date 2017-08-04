#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Vector2.hpp"
using namespace std;
class Matrix2_2
{
public:
	Matrix2_2(Vector2 &v1, Vector2 &v2)
	{
		R1 = v1;
		R2 = v2;
	}
	Vector2 R1, R2;
	Vector2 operator*(const Vector2 &v);
	Matrix2_2 operator*(const Matrix2_2 &M);
};
bool CheckDrawValidation(Vector2 &v);
void main()
{
	initgraph(640, 640);
	setorigin(320, 320);
	setaspectratio(1, -1);
	IMAGE img;
	loadimage(&img, L"C:\\Users\\jack\\desktop\\cg\\Computer_Graphics\\Transformation_Matrix\\Jack.jpg");
	DWORD * pMem = GetImageBuffer(&img);
	Matrix2_2 scale(Vector2(1, 0), Vector2(0, 0.5));
	Matrix2_2 rotation(Vector2(0.707, -0.707), Vector2(0.707, 0.707));
	auto ans = rotation * scale;
	//cout << ans.R1.x << ',' << ans.R1.y << endl;
	//cout << ans.R2.x << ',' << ans.R2.y << endl;
	Matrix2_2 R1(Vector2(1, 1 - 0.707 * 2), Vector2(0, 1));
	Matrix2_2 T(Vector2(1, 0), Vector2(0.707, 1));
	for (int x = 0; x != img.getwidth(); ++x)
		for (int y=img.getheight(); y>=0; --y)
		{
			Vector2 v(x,img.getheight() - y);
			auto result = R1*T*R1*v;
			//Paeth decomposition
			if (CheckDrawValidation(result))
				putpixel(result.x, result.y, pMem[x+img.getheight()*y]);
		}
	//putimage(0, 0, &img);
	_getch();
	closegraph();
}

Vector2 Matrix2_2::operator*(const Vector2 &v)
{
	return Vector2(R1*v, R2*v);
}

bool CheckDrawValidation(Vector2 &v)
{
	if (v.x <= 640 && v.y <= 640)
		return true;
	return false;
}

Matrix2_2 Matrix2_2::operator*(const Matrix2_2 &M)
{
	return Matrix2_2(Vector2(R1*Vector2(M.R1.x, M.R2.x), R1*Vector2(M.R1.y, M.R2.y))
		, Vector2(R2*Vector2(M.R1.x, M.R2.x), R2*Vector2(M.R1.y, M.R2.y)));
}