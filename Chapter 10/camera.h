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
		horizontal = vec3(2.0*half_width, 0.0, 0.0);
		vertical = vec3(0.0, 2.0*half_height, 0.0);
	}

	ray get_ray(float u, float v) const
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

#endif
