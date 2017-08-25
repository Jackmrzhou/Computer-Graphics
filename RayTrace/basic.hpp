#pragma once
#ifndef _BASIC_H
#define _BASIC_H
#include "Vector3.hpp"
#include <string>
constexpr int WindowHeight = 600;
constexpr int WindowWidth = 800;
using namespace std;

class Ray {
public:
	Ray(const Vector3 &v, const Vector3 &o)
	{
		direction.copy(v).normalize();
		origin.copy(o);
	}
	Vector3 direction, origin;
};

class Sample
{
public:
	Sample() {};
	Sample(Vector3 &c, float r)
	{
		color.copy(c), refl = r;
	}
	Vector3 color;
	float refl;
	void copy(const Sample &s);
};
class Object;
class Hit
{
public:
	Hit() { Dist = -1.0f; }
	Hit(Vector3 &p, Vector3 &n, Vector3 &h,float d,Sample *s,const string name)
	{
		Point.copy(p), Norm.copy(n), hVector.copy(h), Dist = d, sample = s, Name = name;
	}
	Vector3 Point, Norm, hVector;
	float Dist;
	Sample *sample;
	string Name;
};

class Object
{
public:
	virtual Hit Intersect(Ray &r) = 0;
};

class Plane:public Object
{
public:
	Plane(const Vector3 &p, const Vector3 &n,const Sample &s)
	{
		Point.copy(p), Norm.copy(n).normalize(), sample.copy(s);
	}
	Vector3 Point, Norm;
	Sample sample;
	virtual Hit Intersect(Ray &r);
};

class Sphere:public Object
{
public:
	Sphere(const Vector3 &c, float r, Sample &s)
	{
		center.copy(c), radius = r, sample.copy(s);
	}
	Vector3 center;
	float radius;
	Sample sample;
	virtual Hit Intersect(Ray &ray);
};

class Camera
{
public:
	Camera(const Vector3 &viewpoint, const Vector3 &viewdirection,
		const Vector3 &up, float dis = 0.5f)
	{
		ViewPoint.copy(viewpoint);
		ViewDirection.copy(viewdirection).normalize();
		UpDirection.copy(up).normalize();
		Right = (ViewDirection ^ UpDirection).normalize();
		distance = dis;
	}
	Vector3 ViewPoint, ViewDirection, UpDirection, Right;
	float distance;
	Ray generate_ray(float x, float y);
};

class Light
{
public:
	Light(Vector3 &p)
	{
		Point.copy(p);
	}
	Vector3 Point;
};
#endif // !_BASIC_H
