
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "im.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"


vec3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;

	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
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

	hitable *list[5];
	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0., -100.5, -1.0), 100.0, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1., 0., -1.0), 0.5, new metal(vec3(0.8, 0.6, 0.2), .2));
	list[3] = new sphere(vec3(-1., 0., -1.0), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1., 0., -1.0), -0.45, new dielectric(1.5));

	hitable *world = new hitable_list(list, 5);

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
				col += color(r, world, 0);
			}

			col /= (float) ns;

			point = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

		}
	}


	FILE *fp = NULL;
	fp = fopen("09.1.bmp", "wb+");
	WriteBMP(fp, im);
}
