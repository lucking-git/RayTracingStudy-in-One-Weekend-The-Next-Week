#pragma once
#include "hittable.h"
//#include "rtweekend.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list :public hittable  //用来存放多个被击中物体的类
{
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const ;
	virtual bool bounding_box(double t0, double t1, aabb& output_box)const ;

public:
	std::vector<shared_ptr<hittable>> objects;  


};
