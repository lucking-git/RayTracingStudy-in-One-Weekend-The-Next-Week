#pragma once
#include "hittable.h"
#include "texture.h"


class constant_medium:public hittable
{
public:
	constant_medium(shared_ptr<hittable> b, double d, shared_ptr<texture> a);

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec)const;
	virtual bool bounding_box(double t0, double t1, aabb& output_box)const;


public:
	shared_ptr<hittable> boundary;
	shared_ptr<material> phase_function;
	double neg_inv_density;


};

