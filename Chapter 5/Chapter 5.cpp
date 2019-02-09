
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = 2.0 * dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant < 0.0)
	{
		return -1.0;
	}

	return (-b - sqrt(discriminant)) / (2.0*a);
}


vec3 color(const ray& r)
{
	vec3 sphere_center(0.0, 0.0, -1.0);
	float sphere_radius(0.5);

	float t = hit_sphere(sphere_center, sphere_radius, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - sphere_center);
		return 0.5 * (N + vec3(1.0, 1.0, 1.0));
		//return vec3(1.0, 0.0, 0.0);
	}
	vec3 unit_direction = unit_vector(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return ((1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0));
}

int main()
{
	int nx = 300;
	int ny = 200;

	Image im(nx, ny);
	int x, y;
	//im.resize(nx, ny);
	vec3 lower_left_corner(-3.0, -2.0, -1.0);
	lower_left_corner *= 0.5;
	lower_left_corner.z = -1.0;
	vec3 horizontal(3.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (y = 0; y < im.height; y++)
	{
		for (x = 0; x < im.width; x++)
		{
			float u = float(x) / float(im.width);
			float v = 1.f - float(y) / float(im.height);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3& point = im.pixel(x, y);
			point = color(r);
		}
	}


	FILE *fp = NULL;
	fp = fopen("05.bmp", "wb+");
	WriteBMP(fp, im);
}
