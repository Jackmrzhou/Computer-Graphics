#include <iostream>
#include <vector>
#include <cmath>
#include "Vector3.hpp"
#include "basic.hpp"
#include <graphics.h>
#include <conio.h>
using namespace std;
constexpr int Height = 640;
constexpr int Width = 640;
LightSource Light(Vector3(1, 1, 0));
HitProperty GetIntersection(Ray &ray,const vector<Sphere*> &v);
Vector3 ComputeColor(HitProperty &p);
void main()
{
    /*Vector3 a(1, 2, 3), b(2, 3, 4);
    auto result = a + b;
    result.out();
    result = a - b;
    result.out();
    auto ans = a * b;
    cout << ans << endl;
    result = a ^ b;
    result.out();
    result.normalize();
    result.out();*/
	//test Vector3
	float sy, sx;
    initgraph(Width, Height);
    Sphere TestSphere(Vector3(-8,0,0), 6, Vector3(200,0,0));
	Sphere TestSphere2(Vector3(8, 0, 0),6, Vector3(0,200,0));
	vector<Sphere*> ObjectGroup;
	ObjectGroup.push_back(&TestSphere);
	ObjectGroup.push_back(&TestSphere2);
    Camera TestCamera(Vector3(0, 0, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
	//circle(200, 200, 100); Test EasyX.
	for (float y = 0; y < Height; ++y)
	{
		sy = 1 - y / Height;
		for (float x = 0; x < Width; ++x)
		{
			sx = x / Width;
			auto ray = TestCamera.generate_ray(sx, sy);
			auto result = GetIntersection(ray, ObjectGroup);
			if (result.distance != 0)
			{
				auto color = ComputeColor(result);
				putpixel(x, y, RGB(color.x, color.y, color.z));
			}
			else
				putpixel(x, y, RGB((1-sy)*255, (1 - sy) * 255, (1 - sy) * 255));
		}
	}
	_getch();
    closegraph();
}

HitProperty GetIntersection(Ray & ray,const vector<Sphere*> &v)
//compute the closest resutl if the ray hits more than one object
{
	bool hit = false;
	HitProperty record, *temp;
	record.distance = INFINITY;
	for (auto &obj : v)
	{
		temp = &obj->Intersection(ray);
		if (temp->distance != 0)
		{
			hit = true;
			if (record.distance > temp->distance)
			{
				record.distance = temp->distance;
				record.NormalVector = temp->NormalVector;
				record.hVector = temp->hVector;
				record.HitColor = temp->HitColor;
			}
			Ray ShadowRay(Light.LightDirection, record.HitPoint);
			for (auto &o : v)
			{
				auto * result = &o->Intersection(ShadowRay);
				if (result->distance != 0)
				{
					record.IsShadow = true;
					break;
				}
			}
		}
	}
	if (hit)
		return record;
	return HitProperty();
}

Vector3 ComputeColor(HitProperty &p)
{
	auto color = Vector3();
	if (p.IsShadow == true)
		return color;
	//in shadow.
	color = p.HitColor.multiply(Light.LightIntensity);
	color = color.multiply(max(0, p.NormalVector*Light.LightDirection));
	//diffuse color
	color = color + Vector3(255, 255, 255).multiply(Light.LightIntensity*pow(max(0, p.NormalVector*p.hVector), 16));
	//specular color
	//no ambient color.
	//set exponent 16
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	//it seems wingdi don't check the validation of RGB
	return color;
}