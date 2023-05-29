#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere:public hittable
{
public:
	sphere() {}
	sphere(vec3 cen, double r) :center(cen), radius(r) {}


	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const;






public:
	vec3 center;
	double radius;



};
