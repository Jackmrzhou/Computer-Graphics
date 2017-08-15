#include <graphics.h>
#include <conio.h>
#include <cmath>
using namespace std;
void DrawLine(int x1,int y1, int x2, int y2);
/*
int main()
{
	initgraph(640, 640);
	DrawLine(200, 600, 400, 200);
	DrawLine(200, 300, 400, 200);
	//line(200, 300, 400, 200);
	//line(200, 600, 400, 200);
	_getch();
	closegraph();
	return 0;
}
*/
void DrawLine(int x1, int y1, int x2, int y2)
{
	int slope;
	if ((y2 - y1)*(x2 - x1) > 0)
		slope = 1;
	else slope = -1;
	if (abs((y2 - y1)*1.0f / (x2 - x1)) <= 1)
	{
		int x3, x4, y;
		if (x1 > x2)
			x3 = x2, x4 = x1, y = y2;
		else
			x3 = x1, x4 = x2, y = y1;
		float d = (y1 - y2)*(x1+1) + (x2 - x1)*(y1+0.5f) + x1*y2 - x2*y1;
		for (int x = x3; x <= x4; ++x)
		{
			putpixel(x, y, RGB(255, 255, 255));
			/*
			if (((y1 - y2)*(x+1) + (x2 - x1)*(y+0.5) + x1*y2 - x2*y1) < 0)
				y += 1;
			//also works, but less efficient.
			*/
			if (d * slope  < 0)
			{
				y += slope;
				d += (x2 - x1)*slope + y1 - y2;
			}
			else
				d += y1 - y2;
			//more efficent.
		}
	}
	else 
	{
		int y3, y4, x;
		if (y1 > y2)
			y3 = y2, y4 = y1, x = x2;
		else
			y3 = y1, y4 = y2, x = x1;
		float d = (y1 - y2)*(x1 + 0.5f) + (x2 - x1)*(y1 + 1) + x1*y2 - x2*y1;
		for (int y = y3; y <= y4; ++y)
		{
			putpixel(x, y, RGB(255, 255, 255));
			if (d * slope < 0)
			{
				x += slope;
				d += x2 - x1 + (y1 - y2)*slope;
			}
			else
				d += x2 - x1;
		}
	}
}