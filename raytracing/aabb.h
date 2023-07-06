#pragma once
#include "rtweekend.h"
class aabb
{
public:
	aabb() {}
	aabb(const vec3& a, const vec3& b);

	vec3 min() const;
	vec3 max() const;
	bool hit(const ray& r, double tmin, double tmax)const;


public:
	vec3 _min;
	vec3 _max;
};

aabb surrounding_box(aabb box0, aabb box1);

