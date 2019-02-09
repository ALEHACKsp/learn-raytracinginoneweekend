#ifndef CAMERAH
#define CAMERAH
#include "ray.h"

class camera {
public:
	camera() :
		lower_left_corner(-3.0, -2.0, -1.0),
		horizontal(3.0, 0.0, 0.0),
		vertical(0.0, 2.0, 0.0),
		origin(0.0, 0.0, 0.0)
	{
		lower_left_corner *= 0.5;
		lower_left_corner.z = -1.0;
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
