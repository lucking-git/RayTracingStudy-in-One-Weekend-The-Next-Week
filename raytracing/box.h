#pragma once
#include "hittable_list.h"

class box:public hittable
{
public:
	box(){}
	box(const vec3& p0, const vec3& p1, shared_ptr<material> ptr);

	virtual bool hit(const ray& r, double t0, double t1, hit_record& rec) const;

	virtual bool bounding_box(double t0, double t1, aabb& output_box)const;


public:
	vec3 box_min;
	vec3 box_max;
	hittable_list sides;

};

