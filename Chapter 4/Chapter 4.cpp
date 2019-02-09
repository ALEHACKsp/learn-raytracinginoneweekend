
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"
#include "ray.h"

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = 2.0 * dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	return (discriminant > 0);
}


vec3 color(const ray& r)
{
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
	{
		return vec3(1.0, 0.0, 0.0);
	}
	vec3 unit_direction = unit_vector(r.direction);
	float t = 0.5 * (unit_direction.y + 1.0);
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
	fp = fopen("04.bmp", "wb+");
	WriteBMP(fp, im);
}
