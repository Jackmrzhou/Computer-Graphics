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
Matrix4 ConstructPerMatrix(Vector3 &p1, Vector3 &p2);
Matrix4 ConstructVpMatrix();
void ProjectionTest(Matrix4 &M);
int main()
{
	initgraph(Height, Width);
	setorigin(0, Height);
	setaspectratio(1, -1);

	Vector3 e(2, 2, 2), g(-1, -0.5, -0.5), t(0, 0, 1);
	auto M_cam = ConstructCamMatrix(e, g, t);
	Vector3 p1(-2, -2, -2), p2(2, 2, -6);
	auto M_orth = ConstructOrthMatrix(p1, p2);
	auto M_vp = ConstructVpMatrix();
	auto M_per = ConstructPerMatrix(p1, p2);
	//auto &P = Matrix4(Vector3(p1.z, 0, 0), Vector3(0, p1.z, 0), Vector3(0, 0, p1.z + p2.z), Vector3(0, 0, -p1.z*p2.z));
	//P.data[3][2] = 1, P.data[3][3] = 0;
	auto M = M_vp*M_orth*M_cam;
	//auto M = M_vp*M_per*M_cam;
	ProjectionTest(M);
	_getch();
	closegraph();
	return 0;
}

void ProjectionTest(Matrix4 &M)
{
	auto Lines = GetSample();
	for (auto it : Lines)
	{
		auto p = M*it->a;
		float w_p = M.data[3][0] * it->a.x + M.data[3][1] * it->a.y + M.data[3][2] * it->a.z + M.data[3][3];
		auto q = M*it->b;
		float w_q = M.data[3][0] * it->b.x + M.data[3][1] * it->b.y + M.data[3][2] * it->b.z + M.data[3][3];
		line(p.x/w_p, p.y/w_p, q.x/w_q, q.y/w_q);
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
	return Matrix4(c1,c2,c3, Vector3(0,0,0)) * 
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

Matrix4 ConstructPerMatrix(Vector3 &p1, Vector3 &p2)
{
	auto &c1 = Vector3(2.0f * p1.z / (p2.x - p1.x), 0, 0);
	auto &c2 = Vector3(0, 2.0f * p1.z / (p2.y - p1.y), 0);
	auto &c3 = Vector3((p1.x + p2.x) / (p1.x - p2.x), (p1.y + p2.y) / (p1.y - p2.y), (p1.z + p2.z) / (p1.z - p2.z));
	auto &c4 = Vector3(0, 0, 2.0f * p1.z*p2.z / (p2.z - p1.z));
	auto M = Matrix4(c1, c2, c3, c4);
	M.data[3][2] = 1, M.data[3][3] = 0;
	return M;
}