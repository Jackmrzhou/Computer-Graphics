#include "basic.hpp"
#include <cmath>
using namespace std;
extern Light gLight;
Ray Camera::generate_ray(float x, float y)
{
	return Ray((ViewDirection.multiply(0.5f) + Right.multiply(x - 0.5f) + UpDirection.multiply(y*0.75 - 0.375f)),
		ViewPoint);
}

void Sample::copy(const Sample &s)
{
	color.copy(s.color), refl = s.refl;
}


Hit Plane::Intersect(Ray &r)
{
	auto a = r.direction * Norm;
	if (a >= 0)
		return Hit();
	float t = ((Point-r.origin)*Norm) / a;
	auto point = r.direction.multiply(t) + r.origin;
	auto hVec = ((gLight.Point - point).normalize() - r.direction).normalize();
	return Hit(point, Norm, hVec, t, &sample, "Plane");
}

Hit Sphere::Intersect(Ray &ray)
{
	Vector3 v = ray.origin - center;
	float a = v.sqrLenth() - radius * radius;
	float DdotV = ray.direction * v;
	if (DdotV <= 0)
	{
		float discr = DdotV * DdotV - a;
		if (discr >= 0)
		{
			float t = -DdotV - sqrt(discr);
			Vector3 Point(ray.origin + ray.direction.multiply(t));
			Vector3 NormalVector = (Point - center) / radius;
			Vector3 hVector = ((gLight.Point - Point).normalize() - ray.direction).normalize();
			return Hit(Point, NormalVector, hVector, t, &sample, "Sphere");
		}
	}
	return Hit();//means no hit
}