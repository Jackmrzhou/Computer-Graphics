#ifndef _Basic_H
#define _Basic_H

class HitProperty
{
public:
	HitProperty() { distance = 0.0f; };
	HitProperty(const Vector3 &n, const Vector3 &h,const Vector3 &c,const Vector3 &p, float d)
	{
		NormalVector.copy(n).normalize();
		hVector.copy(h).normalize();
		HitColor.copy(c);
		HitPoint.copy(p);
		distance = d;
	}
	HitProperty(const HitProperty *p)
	{
		NormalVector = p->NormalVector;
		hVector = p->hVector;
		distance = p->distance;
		HitColor = p->HitColor;
		HitPoint = p->HitPoint;
	}
	Vector3 NormalVector, hVector, HitColor, HitPoint;
	float distance;
	bool IsShadow = false;
	void copy(HitProperty *p);
};

class LightSource
{
public:
	LightSource(const Vector3 &v)
	{
		LightIntensity = 1;
		LightDirection.copy(v).normalize();
	}
	LightSource(const Vector3 &v, float i)
	{
		LightDirection.copy(v).normalize();
		LightIntensity = i;
	}
	Vector3 LightDirection;
	float LightIntensity;
};

class Ray {
public:
	Ray(const Vector3 &v, const Vector3 &o)
	{
		direction.copy(v).normalize();
		origin.copy(o);
	}
	Vector3 direction, origin;
};
class Sphere {
public:
	Sphere(const Vector3 &v, float r, const Vector3 &c)
	{
		center.copy(v);
		color.copy(c);
		Radius = r;
	}
	Vector3 center, color;
	float Radius;
	
	HitProperty Intersection(Ray &ray);
};

class Camera {
public:
	Camera(const Vector3 &viewpoint, const Vector3 &viewdirection,
		const Vector3 &up)
	{
		ViewPoint.copy(viewpoint);
		ViewDirection.copy(viewdirection).normalize();
		UpDirection.copy(up).normalize();
		Right = (ViewDirection ^ UpDirection).normalize();
		distance = 0.5;
	}
	Camera(const Vector3 &viewpoint, const Vector3 &viewdirection,
		const Vector3 &up, float dis)
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

class TestGround
{
public:
	TestGround(const Vector3 &n, const Vector3 &p)
	{
		NormalVector.copy(n);
		Point.copy(p);
	}
	Vector3 NormalVector, Point;
	HitProperty Intersection(Ray &ray);
};
#endif