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
	Camera TestCamera(Vector3(14, 6, 6), Vector3(-1, 0, -0.1), Vector3(-0.1, 0, 1));
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
	p.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 1, 0), Sample(Vector3(191, 64, 64), 0)));
	p.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 0, 1), Sample(Vector3(191, 191, 191), 0.5f)));
	p.push_back(new Plane(Vector3(0, 12, 0), Vector3(0, -1, 0), Sample(Vector3(64, 64, 191), 0)));
	p.push_back(new Plane(Vector3(0, 0, 10), Vector3(0, 0, -1), Sample(Vector3(191, 191, 191), 0)));
}

void GetTestSpheres(vector<Object*> &o)
{
	o.push_back(new Sphere(Vector3(3, 3, 2), 2, Sample(Vector3(255, 255, 255), 1)));
	o.push_back(new Sphere(Vector3(4, 8, 2.7), 2.7f, Sample(Vector3(255, 0, 0), 0)));
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
		Ray ShadowRay(gLight.Point - hit.Point, hit.Point);
		auto sHit = Intersect(ShadowRay, obj);
		if (sHit.Name != "Sphere")
		{
			auto diff = c.multiply(max(0, hit.Norm*((gLight.Point - hit.Point).normalize())));
			auto spec = Vector3(255, 255, 255).multiply(pow(max(0, hit.Norm*hit.hVector), 16));
			color = color + diff + spec;
			if (hit.sample->refl > 0 && ++depth != 5)
			{
				Ray RefRay(r.direction - hit.Norm.multiply(r.direction*hit.Norm * 2), hit.Point);
				auto refcolor = RayTrace(RefRay, obj, depth).multiply(hit.sample->refl);
				color = color.multiply(1-hit.sample->refl) 
					+ Vector3(color.x*refcolor.x / 255, color.y*refcolor.y / 255, color.z*refcolor.z / 255);
			}
				
		}
		ValidateColor(color);
		return color;
	}
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
}
/*
Vector3 ComputeColor(Hit &p)
{
	float k_a = 0.2;
	auto color = p.sample.color;
	auto ambient = color.multiply(k_a);
	//ambient color
	auto diff = color.multiply(max(0, p.Norm*((gLight.Point - p.Point).normalize())));
	//diffuse color
	auto spec = Vector3(255, 255, 255).multiply(pow(max(0, p.Norm*p.hVector), 16));
	//specular color
	color = ambient + diff + spec;
	//set exponent 16
	ValidateColor(color);
	//it seems wingdi don't check the validation of RGB
	return color;
}
*/
inline void ValidateColor(Vector3 &color)
{
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
}