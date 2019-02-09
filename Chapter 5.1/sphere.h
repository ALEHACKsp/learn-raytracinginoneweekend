#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


class sphere: public hitable
{
	public:
		sphere(){};
		sphere(vec3 c, float r) { center = c; radius = r; };
		bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;


		vec3  center;
		float radius;
};


bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0.0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp > t_min && temp < t_max)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp > t_min && temp < t_max)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}
#endif