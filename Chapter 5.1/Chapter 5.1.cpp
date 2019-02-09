
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

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


vec3 color(const ray& r, hitable* world)
{
	hit_record rec;

	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		vec3 N = rec.normal;
		return 0.5 * (N + vec3(1.0, 1.0, 1.0));
		
	}
	vec3 unit_direction = unit_vector(r.direction);
	float t = 0.5 * (unit_direction.y + 1.0);
	return ((1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0));
}

int main()
{
	int nx = 300;
	int ny = 200;

	hitable *list[2];
	list[0] = new sphere(vec3(0., 0., -1.), 0.5);
	list[1] = new sphere(vec3(0., -100.5, -1.), 100.0);

	hitable *world = new hitable_list(list, 2);


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
			point = color(r, world);
		}
	}


	FILE *fp = NULL;
	fp = fopen("05.1.bmp", "wb+");
	WriteBMP(fp, im);
}
