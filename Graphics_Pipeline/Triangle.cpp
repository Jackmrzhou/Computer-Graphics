#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <array>
using namespace std;
struct vertex {
	vertex(float a, float b) { x = a, y = b; }
	float x, y;
};
void DrawTriangle(const array<vertex, 3> &v);
int main()
{
	initgraph(640, 640);
	DrawTriangle(array<vertex,3> {vertex(100, 100), vertex(400, 200), vertex(250, 400)});
	_getch();
	closegraph();
	return 0;
}

void DrawTriangle(const array<vertex, 3> &v)
{
	int ymin = v.begin()->y, xmin = v.begin()->x;
	int ymax = ymin, xmax = xmin;
	for (auto &it : v)
	{
		ymin = ymin > it.y ? it.y : ymin;
		ymax = ymax < it.y ? it.y : ymax;
		xmin = xmin > it.x ? it.x : xmin;
		xmax = xmax < it.x ? it.x : xmax;
	}
	float fa = (v[1].y - v[2].y)*v[0].x + (v[2].x - v[1].x)*v[0].y + v[1].x*v[2].y - v[2].x*v[1].y;
	float fb = (v[2].y - v[0].y)*v[1].x + (v[0].x - v[2].x)*v[1].y + v[2].x*v[0].y - v[0].x*v[2].y;
	float fc = (v[0].y - v[1].y)*v[2].x + (v[1].x - v[0].x)*v[2].y + v[0].x*v[1].y - v[1].x*v[0].y;
	float a, b, c;
	float fa_n = -v[1].y + v[2].y - v[2].x + v[1].x + v[1].x*v[2].y - v[2].x*v[1].y;
	float fb_n = -v[2].y + v[0].y - v[0].x + v[2].x + v[2].x*v[0].y - v[0].x*v[2].y;
	float fc_n = -v[0].y + v[1].y - v[1].x + v[0].x + v[0].x*v[1].y - v[1].x*v[0].y;
	for (int x = xmin; x<xmax; ++x)
		for (int y = ymin; y < ymax; ++y)
		{
			a = ((v[1].y - v[2].y)*x + (v[2].x - v[1].x)*y + v[1].x*v[2].y - v[2].x*v[1].y) / fa;
			b = ((v[2].y - v[0].y)*x + (v[0].x - v[2].x)*y + v[2].x*v[0].y - v[0].x*v[2].y) / fb;
			c = ((v[0].y - v[1].y)*x + (v[1].x - v[0].x)*y + v[0].x*v[1].y - v[1].x*v[0].y) / fc;
			if (a >= 0 && b >= 0 && c >= 0)
				if ((a > 0 || fa*fa_n > 0) && (b > 0 || fb*fb_n > 0) && (c > 0 || fc*fc_n > 0))
				{
					auto color = RGB(a*255, b*255, c*255);
					putpixel(x, y, color);
				}
		}
}

