#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include "basic.hpp"
#include "Vector3.hpp"
using namespace std;
Light gLight(Vector3(6, 6, 10));

void GetTestPlanes(vector<Object*> &p);
void GetTestSpheres(vector<Object*> &o);
Vector3 RayTrace(Ray &r, vector<Object*> &obj, int depth);
Hit Intersect(Ray &r, vector<Object*> &Planes);
inline void ValidateColor(Vector3 &color);
//Vector3 ComputeColor(Hit &p);

int main(void)
{
	initgraph(WindowWidth, WindowHeight);
	vector<Object*> obj;
	GetTestPlanes(obj);
	GetTestSpheres(obj);
	Camera TestCamera(Vector3(14, 6, 6), Vector3(-1, 0, -0.1f), Vector3(-0.1f, 0, 1));
	float sx, sy;
	for (float y = 0; y < WindowHeight; ++y)
	{
		sy = 1 - y / WindowHeight;
		for (float x = 0; x < WindowWidth; ++x)
		{
			sx = x / WindowWidth;
			auto ray = TestCamera.generate_ray(sx, sy);
			auto color = RayTrace(ray, obj, 1);
			putpixel((int)x, (int)y, RGB(color.x, color.y, color.z));
		}
	}
	_getch();
	closegraph();
	return 0;
}
void GetTestPlanes(vector<Object*> &p)
{
	p.push_back(new Plane(Vector3(0, 0, 0), Vector3(1, 0, 0), Sample(Vector3(), 0)));
	//front
	p.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 1, 0), Sample(Vector3(191, 64, 64), 0)));
	//left
	p.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 0, 1), Sample(Vector3(191, 191, 191), 0.5f)));
	//down
	p.push_back(new Plane(Vector3(0, 12, 0), Vector3(0, -1, 0), Sample(Vector3(64, 64, 191), 0)));
	//right
	p.push_back(new Plane(Vector3(0, 0, 10), Vector3(0, 0, -1), Sample(Vector3(191, 191, 191), 0)));
	//up
}

void GetTestSpheres(vector<Object*> &o)
{
	o.push_back(new Sphere(Vector3(3, 3, 2), 2, Sample(Vector3(255, 255, 255), 1)));
	//left ball, totally reflective
	o.push_back(new Sphere(Vector3(4, 8, 2.7f), 2.7f, Sample(Vector3(255, 0, 0), 0)));
	//right ball, totally not reflective
}

Vector3 RayTrace(Ray &r, vector<Object*> &obj, int depth)
{
	Vector3 color;
	auto hit = Intersect(r, obj);
	if (hit.Dist != -1.0f)
	{
		auto c = hit.sample->color;
		auto ambient = c.multiply(0.2f);
		color = color + ambient;
		//ambient color should always be added
		Ray ShadowRay(gLight.Point - hit.Point, hit.Point);
		auto sHit = Intersect(ShadowRay, obj);
		if (sHit.Name != "Sphere")
		{
			auto diff = c.multiply(max(0, hit.Norm*((gLight.Point - hit.Point).normalize())));
			auto spec = Vector3(255, 255, 255).multiply(pow(max(0, hit.Norm*hit.hVector), 16));
			color = color + diff + spec;
		}
		//check shadow
		if (hit.sample->refl > 0 && ++depth != 5)
		{
			Ray RefRay(r.direction - hit.Norm.multiply(r.direction*hit.Norm * 2), hit.Point);
			auto refcolor = RayTrace(RefRay, obj, depth).multiply(hit.sample->refl);
			color = color.multiply(1-hit.sample->refl) 
				+ Vector3(color.x*refcolor.x / 255, color.y*refcolor.y / 255, color.z*refcolor.z / 255);
		}
		//check reflection
	}
	ValidateColor(color);
	return color;
}

Hit Intersect(Ray &r, vector<Object*> &obj)
{
	float dist = INFINITY;
	Hit mhit;
	for (unsigned int i = 0; i < obj.size(); ++i)
	{
		auto hit = obj[i]->Intersect(r);
		if (hit.Dist != -1.0f && hit.Dist < dist)
		{
			dist = hit.Dist;
			mhit = hit;
		}
	}
	return mhit;
	//return the closest hit
}

inline void ValidateColor(Vector3 &color)
{
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
}