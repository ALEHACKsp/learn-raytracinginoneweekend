#ifndef CAMERAH
#define CAMERAH
#include "ray.h"

#define M_PI 3.14159265359

class camera {
public:
	camera(float vfov, float aspect): origin(0.0, 0.0, 0.0)
	{
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		lower_left_corner = vec3(-half_width, -half_height, - 1.0);
		horizontal = 2 * half_width * vec3(1.0, 0.0, 0.0);
		vertical   = 2 * half_height * vec3(0.0, 1.0, 0.0);
	}

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
	{
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;

		origin = lookfrom;
		vec3 w = unit_vector(lookfrom - lookat);
		vec3 u = unit_vector(cross(vup, w));
		vec3 v = cross(w, u);

		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width * u;
		vertical   = 2 * half_height * v;
	}

	ray get_ray(float u, float v) const
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

#endif
