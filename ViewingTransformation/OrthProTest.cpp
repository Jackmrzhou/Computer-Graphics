#include <graphics.h>
#include <cmath>
#include <conio.h>
#include "Matrix4.hpp"
#include "Vector3.hpp"
#include <vector>
using namespace std;
class Line
{
public:
	Line(const Vector3&v1, const Vector3&v2)
	{
		a = v1, b = v2;
	}
	Vector3 a, b;
};
constexpr int Height = 640;
constexpr int Width = 640;
vector<Line*> GetSample();
Matrix4 ConstructCamMatrix(Vector3 &e,Vector3 &g,Vector3 &t);
Matrix4 ConstructOrthMatrix(Vector3 &p1, Vector3 &p2);
Matrix4 ConstructVpMatrix();
void OrthProjTest();
int main()
{
	initgraph(Height, Width);
	setorigin(0, Height);
	setaspectratio(1, -1);
	OrthProjTest();
	_getch();
	closegraph();
	return 0;
}

void OrthProjTest()
{
	auto Lines = GetSample();
	Vector3 e(3, 3, 3), g(-1, -1.2, -1.1), t(-1, -1, 1);
	auto M_cam = ConstructCamMatrix(e, g, t);
	Vector3 p1(-2, -2, 2), p2(2, 2, -2);
	auto M_orth = ConstructOrthMatrix(p1, p2);
	auto M_vp = ConstructVpMatrix();
	auto M = M_vp*M_orth*M_cam;
	for (auto it : Lines)
	{
		auto p = M*it->a;
		auto q = M*it->b;
		line(p.x, p.y, q.x, q.y);
	}
	for (auto &it : Lines)
		delete it;
}

vector<Line*> GetSample()
{
	vector<Line *> Sample;
	Sample.push_back(new Line(Vector3(0, 0, 0), Vector3(1, 0, 0)));
	Sample.push_back(new Line(Vector3(1, 0, 0), Vector3(1, 1, 0)));
	Sample.push_back(new Line(Vector3(1, 1, 0), Vector3(0, 1, 0)));
	Sample.push_back(new Line(Vector3(0, 1, 0), Vector3(0, 0, 0)));

	Sample.push_back(new Line(Vector3(0, 0, 0), Vector3(0, 0, 1)));
	Sample.push_back(new Line(Vector3(1, 0, 0), Vector3(1, 0, 1)));
	Sample.push_back(new Line(Vector3(1, 1, 0), Vector3(1, 1, 1)));
	Sample.push_back(new Line(Vector3(0, 1, 0), Vector3(0, 1, 1)));

	Sample.push_back(new Line(Vector3(0, 0, 1), Vector3(0, 1, 1)));
	Sample.push_back(new Line(Vector3(0, 1, 1), Vector3(1, 1, 1)));
	Sample.push_back(new Line(Vector3(1, 1, 1), Vector3(1, 0, 1)));
	Sample.push_back(new Line(Vector3(1, 0, 1), Vector3(0, 0, 1)));
	
	return Sample;
}

Matrix4 ConstructCamMatrix(Vector3 &e, Vector3 &g, Vector3 &t)
{
	auto &w = g.normalize().multiply(-1);
	auto &u = (t^w).normalize();
	auto &v = w^u;
	auto c1 = Vector3(u.x, v.x, w.x);
	auto c2 = Vector3(u.y, v.y, w.y);
	auto c3 = Vector3(u.z, v.z, w.z);
	return Matrix4(c1,c2,c3, Vector3()) * 
		Matrix4(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1), e.multiply(-1));
}


Matrix4 ConstructOrthMatrix(Vector3 &p1, Vector3 &p2)
{
	auto &c1 = Vector3(2 / (p2.x - p1.x), 0, 0);
	auto &c2 = Vector3(0, 2 / (p2.y - p1.y), 0);
	auto &c3 = Vector3(0, 0, 2 / (p1.z - p2.z));
	auto &c4 = Vector3(-(p2.x + p1.x) / (p2.x - p1.x), -(p2.y + p1.y) / (p2.y - p1.y), -(p2.z + p1.z) / (p1.z - p2.z));
	return Matrix4(c1, c2, c3, c4);
}

Matrix4 ConstructVpMatrix()
{
	return Matrix4(Vector3(Width / 2, 0, 0), Vector3(0, Height / 2, 0), Vector3(0, 0, 1),
		Vector3((Width - 1) / 2, (Height - 1) / 2, 0));
}