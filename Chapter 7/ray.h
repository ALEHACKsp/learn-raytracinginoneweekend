
#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
	ray() {}
	ray(const vec3& a, const vec3& b) { origin = a; direction = b;}
	//ray(const vec3& a, const vec3& b):origin(a),direction(b) { }
	inline vec3 point_at_parameter(float t) const { return origin + t * direction; }
	vec3 origin;
	vec3 direction;
};


inline bool operator==(const ray &r1, const ray &r2) {
	return (r1.origin == r2.origin && r1.direction == r2.direction);
}

#endif


