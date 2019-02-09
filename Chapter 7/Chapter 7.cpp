
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include <assert.h>





float drand48() 
{
	return float(rand()) / RAND_MAX;
}


vec3 random_in_unit_sphere() 
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);

	return p;
}

vec3 color(const ray& r, hitable* world)
{
	hit_record rec;

	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(ray(rec.p, target-rec.p), world);

	}
	vec3 unit_direction = unit_vector(r.direction);
	float t = 0.5 * (unit_direction.y + 1.0);
	return ((1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0));
}

int main()
{
	int nx = 300;
	int ny = 200;
	int ns = 100;

	hitable *list[2];
	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere(vec3(0., -100.5, -1.0), 100.0);

	hitable *world = new hitable_list(list, 2);


	Image im(nx, ny);
	int x, y, s;
	//im.resize(nx, ny);
	camera cam;

	float u, v;

	for (y = 0; y < im.height; y++)
	{
		for (x = 0; x < im.width; x++)
		{
			vec3& point = im.pixel(x, y);

			vec3 col(0.0, 0.0, 0.0);

			for (s = 0; s < ns; s++)
			{
				float u = float(x + drand48()) / float(im.width);
				float v = 1.f - float(y + drand48()) / float(im.height);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}

			col /= (float) ns;
			point = vec3(sqrt(col.r), sqrt(col.g), sqrt(col.b));

		}
	}


	FILE *fp = NULL;
	fp = fopen("07.3.bmp", "wb+");
	WriteBMP(fp, im);
}
