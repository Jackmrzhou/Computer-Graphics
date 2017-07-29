#include <cmath>
#include "Vector3.hpp"
#include "basic.hpp"
extern LightSource Light;
using namespace std;
void HitProperty::copy(HitProperty *p)
{
	distance = p->distance;
	NormalVector = p->NormalVector;
	hVector = p->hVector;
	HitColor = p->HitColor;
	HitPoint = p->HitPoint;
}

Ray Camera::generate_ray(float x,float y)
{
    return Ray((ViewDirection.multiply(0.5) + Right.multiply(x-0.5) + UpDirection.multiply(y-0.5)),
               ViewPoint);
}

HitProperty Sphere::Intersection(Ray &ray)
{
    Vector3 v = ray.origin - center;
    float a = v.sqrLenth() - Radius * Radius;
    float DdotV = ray.direction * v;
	if (DdotV <= 0)
	{
		float discr = DdotV * DdotV - a;
		if (discr >= 0)
		{
			float t = -DdotV - sqrt(discr);
			Vector3 Point(ray.origin + ray.direction.multiply(t));
			Vector3 NormalVector = (Point- center) / Radius;
			Vector3 hVector = (Light.LightDirection - ray.direction).normalize();
			return HitProperty(NormalVector, hVector, color,Point, t);
		}
	}
    return HitProperty();//means no hit
}

HitProperty TestGround::Intersection(Ray &ray)
{
	float t = (Point*NormalVector) / (ray.direction*NormalVector);
	Vector3 HitPoint(ray.origin + ray.direction.multiply(t));
	if ((int)abs((floor(HitPoint.x*0.5)) +floor(HitPoint.y*0.5)) % 2 < 1)
		return HitProperty(NormalVector, Vector3(), Vector3(0,0,0), HitPoint, t);
	return HitProperty(NormalVector, Vector3(), Vector3(150, 150, 150), HitPoint, t);
}