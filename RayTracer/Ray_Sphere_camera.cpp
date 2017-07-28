#include <cmath>
#include "Vector3.hpp"
#include "basic.hpp"
extern LightSource Light;
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
	if (DdotV < 0)
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